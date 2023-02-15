#include "factory.hpp"

#include <cstdlib>
#include <functional>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>

namespace StronglyCoupled
{
    class MusicApp
    {
    public:
        MusicApp() = default;

        void play(const std::string& track_title)
        {
            // creation of product
            SpotifyService music_service("spotify_user", "rjdaslf276%2", 45);

            // usage of product
            std::optional<Track> track = music_service.get_track(track_title);

            if (track)
            {
                std::cout << "Playing track: ";
                for (const auto& note : *track)
                    std::cout << note << ".";
                std::cout << "|\n";
            }
            else
            {
                std::cout << "Track not found!\n";
            }
        }
    };
}

namespace Canonical
{
    class MusicApp
    {
        std::shared_ptr<MusicServiceCreator> music_service_creator_;

    public:
        MusicApp(std::shared_ptr<MusicServiceCreator> music_service_creator)
            : music_service_creator_(music_service_creator)
        {
        }

        void reset_music_service_creator(std::shared_ptr<MusicServiceCreator> new_music_service_creator)
        {
            music_service_creator_ = new_music_service_creator;
        }

        void play(const std::string& track_title)
        {
            // creation of the object
            std::unique_ptr<MusicService> music_service = music_service_creator_->create_music_service();

            // usage of the object
            std::optional<Track> track = music_service->get_track(track_title);

            if (track)
            {
                std::cout << "Playing track: ";
                for (const auto& note : *track)
                    std::cout << note << ".";
                std::cout << "|\n";
            }
            else
            {
                std::cout << "Track not found!\n";
            }
        }
    };

    // parametrized factory
    using MusicServiceFactory = std::unordered_map<std::string, std::shared_ptr<MusicServiceCreator>>;
}

// Modern C++
using MusicServiceCreator = std::function<std::unique_ptr<MusicService>()>;

class MusicApp
{
    MusicServiceCreator music_service_creator_;

public:
    MusicApp(MusicServiceCreator music_service_creator)
        : music_service_creator_(music_service_creator)
    {
    }

    void reset_music_service_creator(MusicServiceCreator new_music_service_creator)
    {
        music_service_creator_ = new_music_service_creator;
    }

    void play(const std::string& track_title)
    {
        // creation of the object
        std::unique_ptr<MusicService> music_service = music_service_creator_();

        // usage of the object
        std::optional<Track> track = music_service->get_track(track_title);

        if (track)
        {
            std::cout << "Playing track: ";
            for (const auto& note : *track)
                std::cout << note << ".";
            std::cout << "|\n";
        }
        else
        {
            std::cout << "Track not found!\n";
        }
    }
};

class TidalServiceCreator
{
    std::string user_name_;
    std::string secret_;

public:
    TidalServiceCreator(const std::string& user_name, const std::string& secret)
        : user_name_{user_name}
        , secret_{secret}
    {
    }

    std::unique_ptr<MusicService> operator()()
    {
        return std::make_unique<TidalService>(user_name_, secret_);
    }
};

void using_canonical_impl()
{
    using namespace Canonical;

    Canonical::MusicServiceFactory music_service_factory;
    music_service_factory.emplace("Tidal", std::make_shared<Canonical::TidalServiceCreator>("tidal_user", "KJH8324d&df"));
    music_service_factory.emplace("Spotify", std::make_shared<SpotifyServiceCreator>("spotify_user", "rjdaslf276%2", 45));
    music_service_factory.emplace("Filesystem", std::make_shared<FsMusicServiceCreator>());

    std::string id_from_config = "Spotify";
    Canonical::MusicApp app(music_service_factory.at(id_from_config));
    app.play("Would?");

    app.reset_music_service_creator(music_service_factory.at("Tidal"));
    app.play("Lux AEterna");
}

using MusicServiceFactory = std::unordered_map<std::string, MusicServiceCreator>;

int main()
{
    MusicServiceFactory music_service_factory;
    music_service_factory.emplace("Tidal", TidalServiceCreator("tidal_user", "KJH8324d&df"));
    music_service_factory.emplace("Spotify", []() { return std::make_unique<SpotifyService>("spotify_user", "rjdaslf276%2", 45);});
    music_service_factory.emplace("Filesystem", &std::make_unique<FilesystemMusicService>);

    std::string id_from_config = "Spotify";
    MusicApp app(music_service_factory.at(id_from_config));
    app.play("Would?");

    app.reset_music_service_creator(music_service_factory.at("Tidal"));
    app.play("Lux AEterna");
}

struct Shape
{
    virtual void draw() = 0;
    virtual void move_to(int x, int y) = 0;
    virtual ~Shape() = default;
};

struct Rectangle : public Shape
{
    int x, y, w, h;

    Rectangle(int x, int y, int w, int h) : x{x}, y{y}, w{w}, h{h}
    {}

    void draw() override
    {
        std::cout << "Rect: " << x << ", " << y << ", " << w << ", " << h << "\n";
    }

    void move_to(int x, int y) override
    {
        this->x = x;
        this->y = y;
    }
};

struct Circle : public Shape
{
    int x, y, r;

    Circle(int x, int y, int r) : x{x}, y{y}, r{r}
    {}

    virtual void draw() override
    {
        std::cout << "Circle: " << x << ", " << y << ", " << r << "\n";
    }

    virtual void move_to(int x, int y) override
    {
        this->x = x;
        this->y = y;
    }
};

void foo()
{
    std::cout << "foo()\n";
}

struct Foo
{
    void operator()() 
    {
        std::cout << "Foo::operator()()\n";
    }
};

class Function
{
    virtual void call() = 0;
    virtual ~Function() = default;
};

void duck_typing()
{
    std::unique_ptr<Shape> shp = std::make_unique<Rectangle>(100, 200, 600, 500);
    shp->draw();
    shp->move_to(100, 200);

    shp = std::make_unique<Circle>(200, 600, 100);
    shp->draw();
    shp->move_to(100, 200);

    // duck typing
    // Shape shp = Rectangle(100, 200, 600, 500);
    // shp.draw();
    // shp.move_to(100, 300);

    // shp = Circle(100, 300, 800);
    // shp.draw();
    // shp.move_to(100, 400);

    std::function<void()> f;

    f = foo;
    f();

    f = Foo{};
    f();

    f = []() { std::cout << "Lambda\n"; };
    f();
}