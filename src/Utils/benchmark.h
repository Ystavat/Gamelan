#ifndef __BENCHMARK_H__
#define __BENCHMARK_H__

#include "core.h"
#include <chrono>

#ifdef AUTO_FLUSH
	#define FLUSH(stream) stream.flush()
#else
	#define FLUSH(stream)
#endif


namespace Benchmark {
	enum State {
		Out, Start, In
	};

	struct Entry {
		std::string name;
		long long start;
		long long stop;
		uint32_t threadID;
	};

	class Writer {
		private:
			std::ofstream m_outputStream;
			int m_state;

			Writer(): m_state(Out) {}
			~Writer() {
				if (m_state != Out) {
					endSession();
				}
			}

		public:
			static Writer& get() {
				static Writer instance;
				return instance;
			}

			void beginSession(const std::string& filePath = "results.json") {
				m_outputStream.open(filePath);
				m_state = Start;
				writeHeader();
			}

			void endSession() {
				if (m_state == Out) return;
				
				writeFooter();
				m_outputStream.flush();
				m_state = Out;
			}

			void writeHeader() {
				if (m_state == Out) return;

				m_outputStream << "{\"otherData\":{},\"traceEvents\":[";
				FLUSH(m_outputStream);
			}

			void writeFooter() {
				if (m_state == Out) return;

				m_outputStream << "]}";
				FLUSH(m_outputStream);
			}

			void writeEntry(const Entry& entry) {
				if (m_state == Out) return;

				if (m_state == Start) {
					m_state = In;
				} else {
					m_outputStream << ",";
				}
				m_outputStream << "{"
				<< "\"cat\":\"function\","
				<< "\"dur\":" << entry.stop-entry.start << ","
				<< "\"name\":\"" << entry.name << "\","
				<< "\"ph\":\"X\","
				<< "\"pid\":0,"
				<< "\"tid\":" << entry.threadID << ","
				<< "\"ts\":" << entry.start << "}";
				FLUSH(m_outputStream);
			}
	};

	class Timer {
		private:
			const char* m_name;
			std::chrono::time_point<std::chrono::high_resolution_clock> m_startPoint;

		public:
			Timer(const char* name): m_name(name) {
				m_startPoint = std::chrono::high_resolution_clock::now();
			}

			~Timer() {
				std::chrono::time_point<std::chrono::high_resolution_clock> stopPoint = std::chrono::high_resolution_clock::now();
				long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startPoint).time_since_epoch().count();
				long long stop  = std::chrono::time_point_cast<std::chrono::microseconds>(stopPoint).time_since_epoch().count();
				uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
				Writer::get().writeEntry({ m_name, start, stop, threadID });
			}
	};

}


#endif
