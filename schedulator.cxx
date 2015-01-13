#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <cassert>

typedef std::pair<int, int> point_t;

int get_next_id() {
	static int next_id = 0;
	return next_id++;
}

enum days { SEG = 0, TER, QUA, QUI, SEX, SAB, DOM };

enum horarios {
	H_0730_0900 =  0, H_0905_1035, H_1040_1210,
	H_1830_2000 = 15, H_2005_2135, H_2140_2310,
};

const char* dow_txt(const int d) {
	switch (d) {
	case SEG: return "SEG";
	case TER: return "TER";
	case QUA: return "QUA";
	case QUI: return "QUI";
	case SEX: return "SEX";
	case SAB: return "SAB";
	case DOM: return "DOM";
	default:  return "WTF";
	}
}

const char* sch_txt(const int n) {
	switch (n) {
	case H_0730_0900: return "07:30 - 09:00";
	case H_0905_1035: return "09:05 - 10:35";
	case H_1040_1210: return "10:40 - 12:10";
	case H_1830_2000: return "18:30 - 20:00";
	case H_2005_2135: return "20:05 - 21:35";
	case H_2140_2310: return "21:40 - 23:10";
	default:  return "???";
	}
}

struct class_option {
	int id;
	std::vector<point_t > points;

	class_option(const point_t& p0, const int id_ = get_next_id())
	 : id(id_), points({ p0 }) {}

	class_option(const point_t& p0, const point_t& p1, const int id_ = get_next_id())
	 : id(id_), points({ p0, p1 }) {}

	class_option(const point_t& p0, const point_t& p1, const point_t& p2, const int id_ = get_next_id())
	 : id(id_), points({ p0, p1, p2 }) {}

	class_option(const point_t& p0, const point_t& p1, const point_t& p2, const point_t& p3, const int id_ = get_next_id())
	 : id(id_), points({ p0, p1, p2, p3 }) {}
};

struct course_class {
	std::string name;
	std::vector<class_option> options;

	course_class(const std::string& name_)
	 : name(name_) {
	}

	course_class& operator<<(const class_option& option) {
		options.push_back(option);
		return *this;
	}

	bool operator<(const course_class& rhs) const {
		return name < rhs.name;
	}
};

class schedule_solver {
	std::vector<course_class> classes;
	std::vector<int> _numbers;

	bool next_number() {
		assert(_numbers.size() == classes.size());

		bool has_next = true;
		++(*_numbers.rbegin());

		bool carry = false;
		for (int i=_numbers.size()-1; i>=0; --i) {
			int& p = _numbers[i];

			if (carry) {
				++p;
				carry = false;
			}

			if (p >= classes[i].options.size()) {
				carry = true;
				p = 0;

				if (i == 0) {
					has_next = false;
				}
			}
		}

		return has_next;
	}

	bool conflict_free() {
		std::set<point_t> bag;

		//std::cout << '\n';
		for (int i=0; i<_numbers.size(); ++i) {
			auto& points = classes[i].options[_numbers[i]].points;
			for (auto& p : points) {
				//std::cout << '\t' << p.first << '-' << p.second << std::endl;
				auto r = bag.insert(p);

				// If insertion failed, there's a conflict.
				if (r.second == false) {
					return false;
				}
			}
		}

		return true;
	}

public:
	schedule_solver(const course_class& c0)
	 : classes({ c0 }), _numbers(1, 0) {}

	schedule_solver(const course_class& c0, const course_class& c1)
	 : classes({ c0, c1 }), _numbers(2, 0) {}

	schedule_solver(const course_class& c0, const course_class& c1, const course_class& c2)
	 : classes({ c0, c1, c2 }), _numbers(3, 0) {}

	schedule_solver(const course_class& c0, const course_class& c1, const course_class& c2,
			const course_class& c3)
	 : classes({ c0, c1, c2, c3 }), _numbers(4, 0) {}

	schedule_solver(const course_class& c0, const course_class& c1, const course_class& c2,
			const course_class& c3, const course_class& c4)
	 : classes({ c0, c1, c2, c3, c4 }), _numbers(5, 0) {}

	schedule_solver(const course_class& c0, const course_class& c1, const course_class& c2,
			const course_class& c3, const course_class& c4, const course_class& c5)
	 : classes({ c0, c1, c2, c3, c4, c5 }), _numbers(6, 0) {}

	schedule_solver(const course_class& c0, const course_class& c1, const course_class& c2,
			const course_class& c3, const course_class& c4, const course_class& c5,
			const course_class& c6)
	 : classes({ c0, c1, c2, c3, c4, c5, c6 }), _numbers(7, 0) {}

	schedule_solver(const course_class& c0, const course_class& c1, const course_class& c2,
			const course_class& c3, const course_class& c4, const course_class& c5,
			const course_class& c6, const course_class& c7)
	 : classes({ c0, c1, c2, c3, c4, c5, c6, c7 }), _numbers(8, 0) {}

	schedule_solver(const course_class& c0, const course_class& c1, const course_class& c2,
			const course_class& c3, const course_class& c4, const course_class& c5,
			const course_class& c6, const course_class& c7, const course_class& c8)
	 : classes({ c0, c1, c2, c3, c4, c5, c6, c7, c8 }), _numbers(9, 0) {}

	schedule_solver(const course_class& c0, const course_class& c1, const course_class& c2,
			const course_class& c3, const course_class& c4, const course_class& c5,
			const course_class& c6, const course_class& c7, const course_class& c8,
			const course_class& c9)
	 : classes({ c0, c1, c2, c3, c4, c5, c6, c7, c8, c9 }), _numbers(10, 0) {}

	schedule_solver(const course_class& c0, const course_class& c1, const course_class& c2,
			const course_class& c3, const course_class& c4, const course_class& c5,
			const course_class& c6, const course_class& c7, const course_class& c8,
			const course_class& c9, const course_class& c10)
	 : classes({ c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10 }), _numbers(11, 0) {}

	void operator()() {
		size_t solutions_found = 0;

		do {
			if (conflict_free()) {
				++solutions_found;

				std::cout << "Solution:\n";
				for (int i=0; i<_numbers.size(); ++i) {
					const auto& k = classes[i];
					const int winner = _numbers[i];
					const auto& points = k.options[winner].points;
					std::cout << '\t' << k.name << ": ";
					for (const auto& p : k.options[winner].points) {
						std::cout << dow_txt(p.first) << '-' << sch_txt(p.second) << ", ";
					}

					std::cout << '\n';
				}

				//std::copy(std::begin(_numbers), std::end(_numbers), std::ostream_iterator<int>(std::cout, ","));
				//std::cout << std::endl;
			}
		} while (next_number());

		std::cout << "Solutions found: " << solutions_found << std::endl;
	}
};

void do_da_mack() {
	course_class ENEC00057_APD3("LP3");
	ENEC00057_APD3
		//<< class_option(point_t(TER, H_0730_0900))
		  << class_option(point_t(SEX, H_2005_2135))
		  << class_option(point_t(SEG, H_2140_2310))
		  << class_option(point_t(TER, H_2140_2310));

	course_class ENEC00094_IHM("IHM");
	ENEC00094_IHM
		  //<< class_option(point_t(SEG, H_1040_1210))
		  //<< class_option(point_t(TER, H_0905_1035))
		  //<< class_option(point_t(SEG, H_1040_1210))
		  << class_option(point_t(SEG, H_2005_2135))
		  << class_option(point_t(QUI, H_1830_2000))
		  << class_option(point_t(SEG, H_1830_2000))
		  << class_option(point_t(SEG, H_1830_2000));

	course_class ENEC00134_BD1("BD1");
	ENEC00134_BD1
		//<< class_option(point_t(QUA, H_0905_1035), point_t(SEX, H_0905_1035))
		  << class_option(point_t(QUA, H_2140_2310), point_t(TER, H_2005_2135))
		  << class_option(point_t(QUI, H_1830_2000), point_t(TER, H_2005_2135))
		  << class_option(point_t(QUA, H_1830_2000), point_t(TER, H_2140_2310))
		  << class_option(point_t(SEX, H_2140_2310), point_t(TER, H_2140_2310))
		  << class_option(point_t(TER, H_1830_2000), point_t(QUI, H_2005_2135));

	course_class ENEC00147_ES2("ES2");
	ENEC00147_ES2
		//<< class_option(point_t(SEG, H_1040_1210), point_t(QUI, H_1040_1210))
		  << class_option(point_t(QUI, H_1830_2000), point_t(QUI, H_2140_2310))
		  << class_option(point_t(QUA, H_2140_2310), point_t(QUI, H_2140_2310))
		  << class_option(point_t(SEG, H_1830_2000), point_t(SEX, H_1830_2000))
		  << class_option(point_t(TER, H_1830_2000), point_t(SEX, H_1830_2000));

	course_class ENEC00171_SO("SO");
	ENEC00171_SO
		//<< class_option(point_t(SEX, H_0730_0900), point_t(SEX, H_1040_1210))
		  << class_option(point_t(QUA, H_2005_2135), point_t(SEG, H_1830_2000))
		  << class_option(point_t(TER, H_2140_2310), point_t(SEG, H_1830_2000))
		  << class_option(point_t(SEX, H_2005_2135), point_t(SEX, H_2140_2310))
		  << class_option(point_t(QUA, H_1830_2000), point_t(SEX, H_2005_2135));

	course_class ENEC00257_REDES("RDC");
	ENEC00257_REDES
		//<< class_option(point_t(QUA, H_0730_0900), point_t(SEX, H_0905_1035))
		//<< class_option(point_t(TER, H_0730_0900), point_t(QUI, H_0905_1035))
		//<< class_option(point_t(QUA, H_0730_0900), point_t(SEX, H_0905_1035))
		  << class_option(point_t(SEG, H_1830_2000), point_t(QUA, H_2005_2135))
		  << class_option(point_t(SEG, H_2005_2135), point_t(QUA, H_2140_2310))
		  << class_option(point_t(QUA, H_2140_2310), point_t(SEX, H_2140_2310))
		  << class_option(point_t(SEG, H_2140_2310), point_t(QUA, H_1830_2000));

	course_class ENEC00275_LP3("LP3");
	ENEC00275_LP3
		//<< class_option(point_t(TER, H_1040_1210), point_t(SEG, H_0905_1035), point_t(QUI, H_0905_1035))
		//<< class_option(point_t(QUA, H_1040_1210), point_t(SEG, H_0905_1035), point_t(QUI, H_0905_1035))
		  << class_option(point_t(TER, H_2140_2310), point_t(SEG, H_2140_2310), point_t(QUA, H_1830_2000))
		  << class_option(point_t(QUA, H_1830_2000), point_t(QUA, H_2005_2135), point_t(SEG, H_2140_2310))
		  << class_option(point_t(TER, H_1830_2000), point_t(TER, H_2005_2135), point_t(SEG, H_2005_2135))
		  << class_option(point_t(SEG, H_1830_2000), point_t(SEG, H_2005_2135), point_t(TER, H_2005_2135));

	course_class ENEX01022_PARADIGMAS("PLP");
	ENEX01022_PARADIGMAS
		//<< class_option(point_t(QUI, H_1040_1210), point_t(SEG, H_0905_1035))
		  << class_option(point_t(SEX, H_2140_2310), point_t(TER, H_1830_2000));

	course_class ENEX01112_ALGEBRA_LINEAR("ALO");
	ENEX01112_ALGEBRA_LINEAR
		//<< class_option(point_t(SEG, H_0730_0900), point_t(SEX, H_0905_1035))
		  << class_option(point_t(QUI, H_1830_2000), point_t(SEX, H_2005_2135));

	course_class ENEX01131_CALCULO3("C3");
	ENEX01131_CALCULO3
		//<< class_option(point_t(QUA, H_0730_0900), point_t(QUI, H_0730_0900))
		  << class_option(point_t(TER, H_2005_2135), point_t(SEX, H_1830_2000));

	course_class ENEX01387_AN_ALGORITMOS("AA");
	ENEX01387_AN_ALGORITMOS
		//<< class_option(point_t(SEG, H_1040_1210), point_t(QUA, H_0905_1035))
		  << class_option(point_t(SEG, H_2005_2135), point_t(QUA, H_2005_2135));

	schedule_solver solver(
		  ENEC00057_APD3
		, ENEC00094_IHM
		, ENEC00134_BD1
		, ENEC00147_ES2
		, ENEC00171_SO
	//	, ENEC00257_REDES
		, ENEC00275_LP3
		, ENEX01022_PARADIGMAS
	//	, ENEX01112_ALGEBRA_LINEAR
	//	, ENEX01131_CALCULO3
	//	, ENEX01387_AN_ALGORITMOS
	);

	solver();
}

int main(const int argc, const char* argv[]) {
	do_da_mack();
}
