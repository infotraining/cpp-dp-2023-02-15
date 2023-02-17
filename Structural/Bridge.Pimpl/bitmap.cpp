#include "bitmap.hpp"
#include <algorithm>
#include <array>
#include <vector>
#include <list>

using namespace std;

struct Bitmap::BitmapImpl
{
    std::vector<char> image_;
};

Bitmap::Bitmap(size_t size, char fill_char)  
    : pimpl_{std::make_unique<BitmapImpl>()}
{
    pimpl_->image_ = std::vector<char>(size, fill_char);
}

Bitmap::~Bitmap() = default;

void Bitmap::draw()
{
    cout << "Image: ";
    for (size_t i = 0; i < pimpl_->image_.size(); ++i)
        cout << pimpl_->image_[i];
    cout << endl;
}
