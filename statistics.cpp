#include <iostream>
#include <limits>
#include <math.h>
#include <cmath>
#include <vector>
#include <algorithm>

class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char * name() const = 0;
};

class Min : public IStatistics {
public:
	Min() : m_min{std::numeric_limits<double>::max()} {
	}

	void update(double next) override {
		if (next < m_min) {
			m_min = next;
		}
	}

	double eval() const override {
		return m_min;
	}

	const char * name() const override {
		return "min";
	}

private:
	double m_min;
};

class Max : public IStatistics {
public:
	Max() : m_max{std::numeric_limits<double>::min()} {}

	void update(double next) override {
			if (next > m_max) {
				m_max = next;
			}
		}

	double eval() const override {
		return m_max;
	}

	const char * name() const override {
		return "max";
	}

private:
	double m_max;
};

class Mean : public IStatistics {
public:
	Mean() : units_count{0}, sum{0} {};

	void update(double next) override {
		sum += next;
		++units_count;
	}

	double eval() const override {
		return sum/units_count;
	}

	const char * name() const override {
		return "mean";
	}

private:
	int units_count;
	double sum;
};


class Std : public IStatistics {
public:
	Std() : sum{0}, units{std::vector<double>()} {}
	void update(double next) override {
		units.push_back(next);
		sum += next;		
	}
	double eval() const override {
		double mean = get_mean();
		double e_sum = 0;
		for(auto i : units) {
			e_sum += pow(i-mean, 2);
		}
		return sqrt(e_sum/units.size());
	}
	const char * name() const override {
		return "std";
	}
private:
	std::vector<double> units;
	double sum;
	double get_mean() const {
		return sum/units.size();
	}
};

class Pct : public IStatistics {
public:
	Pct(int percent) : units{std::vector<double>()}, percent{percent}{}
	virtual void update(double next) final{
		units.push_back(next);
	};
	virtual double eval() const final{
		return calculatePercentile();
	};
	virtual const char * name() const = 0;
protected:
	mutable std::vector<double> units;
	int percent;
	double calculatePercentile() const {
		std::sort(units.begin(), units.end());
		double pos = (units.size() + 1) * (static_cast<double>(percent)/100);		
		bool hasFraction = fmod(pos, 1.0) != 0.0;
		int lowerPosition = static_cast<int>(std::floor(pos));
		if (!hasFraction && lowerPosition < units.size()) {
        	return units[lowerPosition];
    	} else if (lowerPosition + 1 < units.size()) {
        	return units[lowerPosition] + (pos - std::floor(pos)) * (units[lowerPosition + 1] - units[lowerPosition]);
    	}
    	return units.back();
	}
};

class Pct90 : public Pct {
public:
	Pct90() : Pct{90}{}
	const char * name() const override {
		return "pct90";
	}
};

class Pct95 : public Pct {
public:
	Pct95() : Pct{95}{}
	const char * name() const override {
		return "pct95";
	}
};


int main() {

	const size_t statistics_count = 6;
	IStatistics *statistics[statistics_count];

	statistics[0] = new Min{};
	statistics[1] = new Max{};
	statistics[2] = new Mean{};
	statistics[3] = new Std{};
	statistics[4] = new Pct90{};
	statistics[5] = new Pct95{};


	double val = 0;
	while (std::cin >> val) {
		for (size_t i = 0; i < statistics_count; ++i) {
			statistics[i]->update(val);
		}
	}

	// Handle invalid input data
	if (!std::cin.eof() && !std::cin.good()) {
		std::cerr << "Invalid input data\n";
		return 1;
	}

	// Print results if any
	for (size_t i = 0; i < statistics_count; ++i) {
		std::cout << statistics[i]->name() << " = " << statistics[i]->eval() << std::endl;
	}

	// Clear memory - delete all objects created by new
	for (size_t i = 0; i < statistics_count; ++i) {
		delete statistics[i];
	}

	return 0;
}