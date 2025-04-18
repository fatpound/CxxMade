import FatPound;

import std;

auto main(int, char**) noexcept -> int
{
    try
    {
        std::println<>("fat->pound");
        
        return 0;
    }
    catch (const std::exception& ex)
    {
        static_cast<void>(ex);
    }
    catch (...)
    {
        static_cast<void>(0);
    }
    
    return -1;
}
