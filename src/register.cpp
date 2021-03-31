#include "register.hpp"

using namespace std;

static map<int, int> mapped_pages;

Register::Register(u32 base, u32 offset): offset(offset)
{
    base_hash = base / PAGE_SIZE;
    auto it = mapped_pages.find(base_hash);
    if (it == mapped_pages.end())
    {
        pair<int, int> empty_block = {base_hash, 1};
        mapped_pages.insert(empty_block);
        // init page
        cout << "page init!\n";
    }
    else
    {
        it->second++;
    }
}

Register::~Register()
{
    auto it = mapped_pages.find(base_hash);
    if (it != mapped_pages.end())
    {
        it->second--;

        if (it->second == 0)
        {
            // free page
            cout << "page destroyed\n";
        }
    }
}

void Register::write()
{
}

void Register::read()
{
}