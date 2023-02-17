#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

struct StatResult
{
    std::string description;
    double value;

    StatResult(const std::string& desc, double val)
        : description(desc)
        , value(val)
    {
    }
};

using Data = std::vector<double>;
using Results = std::vector<StatResult>;

using StatCounter = std::function<Results(const Data&)>;

namespace Alternative
{
    using StatCounter = std::function<void(const Data&, Results& out_stats)>;
}

Results GetAvg(const Data& data)
{
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    double avg = sum / data.size();
    return {{"Avg", avg}};
}

struct GetSum
{
    Results operator()(const Data& data)
    {
        double sum = std::accumulate(data.begin(), data.end(), 0.0);
        return {{"Sum", sum}};
    }
};

struct GetMin
{
    Results operator()(const Data& data)
    {
        return {{"Min", *(std::min_element(data.begin(), data.end()))}};
    }
};

struct GetMax
{
    Results operator()(const Data& data)
    {
        return {{"Max", *(std::max_element(data.begin(), data.end()))}};
    }
};

// composite
struct StatGroup
{
    std::vector<StatCounter> stats_;

    Results operator()(const Data& data)
    {
        Results results;

        for(const auto& stat : stats_)
        {
            auto&& stats = stat(data);

            results.insert(results.end(), stats.begin(), stats.end());
        }

        return results;
    }

    void add_stat(StatCounter stat)
    {
        stats_.push_back(stat);
    }
};

class DataAnalyzer
{
    Data data_;
    Results results_;
    StatCounter stat_counter_;

public:
    DataAnalyzer(StatCounter stat_type)
        : stat_counter_{stat_type}
    {
    }

    void load_data(const std::string& file_name)
    {
        data_.clear();
        results_.clear();

        std::ifstream fin(file_name.c_str());
        if (!fin)
            throw std::runtime_error("File not opened");

        double d;
        while (fin >> d)
        {
            data_.push_back(d);
        }

        std::cout << "File " << file_name << " has been loaded...\n";
    }

    void set_statistics(StatCounter stat_type)
    {
        stat_counter_ = stat_type;
    }

    void calculate()
    {
        auto&& stats = stat_counter_(data_);

        results_.insert(results_.end(), stats.begin(), stats.end());
    }

    const Results& results() const
    {
        return results_;
    }
};

void show_results(const Results& results)
{
    for (const auto& rslt : results)
        std::cout << rslt.description << " = " << rslt.value << std::endl;
}

int main()
{
    StatGroup min_max{{GetMin{}, GetMax{}}};
    StatGroup std_stats{{GetAvg, min_max }};
    std_stats.add_stat(GetSum{});

    DataAnalyzer da{std_stats};
    da.load_data("stats_data.dat");
    da.calculate();

    show_results(da.results());

    std::cout << "\n\n";

    da.load_data("new_stats_data.dat");
    da.calculate();

    show_results(da.results());
}
