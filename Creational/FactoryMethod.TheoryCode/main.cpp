#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "factory.hpp"

using namespace std;

class Service
{
    shared_ptr<LoggerCreator> creator_;
    bool is_started_ = false;

public:
    Service(shared_ptr<LoggerCreator> creator)
        : creator_(creator)
    {
    }

    Service(const Service&) = delete;
    Service& operator=(const Service&) = delete;

    void run()
    {
        unique_ptr<Logger> logger = creator_->create_logger();
        if (!is_started_)
            start();
            logger->log("Service has been started...");
        process_requests();
        logger->log("Service has processed all requests...");
    }

protected:
    virtual void start() {}
    virtual void process_requests() {}
};

using LoggerFactory = std::unordered_map<std::string, shared_ptr<LoggerCreator>>;

int main()
{
    LoggerFactory logger_factory;
    logger_factory.insert(make_pair("ConsoleLogger", make_shared<ConsoleLoggerCreator>()));
    logger_factory.insert(make_pair("FileLogger", make_shared<FileLoggerCreator>("data.log")));

    Service srv(logger_factory.at("ConsoleLogger"));
    srv.run();
}
