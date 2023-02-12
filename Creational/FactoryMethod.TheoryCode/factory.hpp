#ifndef FACTORY_HPP_
#define FACTORY_HPP_

#include <fstream>
#include <iostream>
#include <memory>
#include <string>

// "Product"
class Logger
{
public:
    // product's interface
    virtual void log(const std::string& msg) = 0;
    virtual ~Logger() { }
};

// "ConcreteProductA"
class FileLogger : public Logger
{
    std::ofstream log_file_;

public:
    FileLogger(const std::string& logname)
        : log_file_{logname, std::ios::app}
    {
    }

    void log(const std::string& msg)
    {
        log_file_ << "LOG: " << msg << std::endl;
    }
};

// "ConcreteProductB"
class ConsoleLogger : public Logger
{
public:
    void log(const std::string& msg)
    {
        std::cout << "LOG: " << msg << std::endl;
    }
};

// "Creator"
class LoggerCreator
{
public:
    virtual std::unique_ptr<Logger> create_logger() = 0; // factory method
    virtual ~LoggerCreator() = default;
};

// "ConcreteCreatorA"
class FileLoggerCreator : public LoggerCreator
{
    std::string file_name_;

public:
    FileLoggerCreator(const std::string& file_name)
        : file_name_{file_name}
    {
    }

    virtual std::unique_ptr<Logger> create_logger() override
    {
        return std::make_unique<FileLogger>(file_name_);
    }
};

// "ConcreteCreatorB"
class ConsoleLoggerCreator : public LoggerCreator
{
public:
    virtual std::unique_ptr<Logger> create_logger() override
    {
        return std::make_unique<ConsoleLogger>();
    }
};

#endif /*FACTORY_HPP_*/
