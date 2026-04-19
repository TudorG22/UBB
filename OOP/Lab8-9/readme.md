Tools required: clean-tidy, bear

`bear -- g++ -Wall -Wextra -I include src/*.cpp -o app`

`clang-tidy src/*.cpp -checks='cppcoreguidelines-*' -p .`