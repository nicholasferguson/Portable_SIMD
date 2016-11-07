
#include <windows.h>
#include <Wincon.h >

#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>
#include <wctype.h>

#include <algorithm>
#include <iomanip>
#include <limits>
#include <list>
#include <map>
#include <ostream>  // NOLINT
#include <sstream>
#include <vector>



# include <io.h>  // NOLINT
# include <sys/timeb.h>  // NOLINT
# include <sys/types.h>  // NOLINT
# include <sys/stat.h>  // NOLINT


// class PrettyUnitTestResultPrinter

// Always returns true.
bool AlwaysTrue();
class ClassUniqueToAlwaysTrue {};


bool IsTrue(bool condition) { return condition; }

bool AlwaysTrue() {
	return true;
}

// Always returns false.
inline bool AlwaysFalse() { return !AlwaysTrue(); }

enum GTestColor {
	COLOR_DEFAULT,
	COLOR_RED,
	COLOR_GREEN,
	COLOR_YELLOW
};

// Returns the ANSI color code for the given color.  COLOR_DEFAULT is
// an invalid input.
const char* GetAnsiColorCode(GTestColor color) {
	switch (color) {
	case COLOR_RED:     return "1";
	case COLOR_GREEN:   return "2";
	case COLOR_YELLOW:  return "3";
	default:            return NULL;
	};
}
// Returns the character attribute for the given color.
short GetColorAttribute(GTestColor color)
{
	switch (color) {
	case COLOR_RED:    return FOREGROUND_RED;
	case COLOR_GREEN:  return FOREGROUND_GREEN;
	case COLOR_YELLOW: return FOREGROUND_RED | FOREGROUND_GREEN;
	default:           return 0;
	}
}

// Helpers for printing colored strings to stdout. Note that on Windows, we
// cannot simply emit special characters and have the terminal change colors.
// This routine must actually emit the characters rather than return a string
// that would be colored when printed, as can be done on Linux.
void ColoredPrintf(GTestColor color, const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);

#ifdef MSVC
	const bool use_color = true;// AlwaysFalse();
#else
	static const bool in_color_mode =
		ShouldUseColor(posix::IsATTY(posix::FileNo(stdout)) != 0);
	const bool use_color = in_color_mode && (color != COLOR_DEFAULT);
#endif  // GTEST_OS_WINDOWS_MOBILE || GTEST_OS_SYMBIAN || GTEST_OS_ZOS
	// The '!= 0' comparison is necessary to satisfy MSVC 7.1.

	if (!use_color) {
		vprintf(fmt, args);
		va_end(args);
		return;
	}

	const HANDLE stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	// Gets the current text color.
	CONSOLE_SCREEN_BUFFER_INFO buffer_info;
	GetConsoleScreenBufferInfo(stdout_handle, &buffer_info);
	const short old_color_attrs = buffer_info.wAttributes;

	// We need to flush the stream buffers into the console before each
	// SetConsoleTextAttribute call lest it affect the text that is already
	// printed but has not yet reached the console.
	fflush(stdout);
	SetConsoleTextAttribute(stdout_handle,
		GetColorAttribute(color) | FOREGROUND_INTENSITY);
	vprintf(fmt, args);

	fflush(stdout);
	// Restores the text color.
	SetConsoleTextAttribute(stdout_handle, old_color_attrs);

	va_end(args);
}

namespace testing
{
	namespace internal
	{
		enum GTestColor {
			COLOR_DEFAULT,
			COLOR_RED,
			COLOR_GREEN,
			COLOR_YELLOW
		};


	}
}
#define PRINTF(...)  do { ColoredPrintf(COLOR_GREEN, "[          ] "); ColoredPrintf(COLOR_YELLOW, __VA_ARGS__); } while(0)

// C++ stream interface
class TestCout : public std::stringstream
{
public:
	~TestCout()
	{
		PRINTF("%s", str().c_str());
	}
};

#define TEST_COUT  TestCout()

/*
TEST(pa_acq, Foo)
{
// C style
// PRINTF("Hello world \n");

// or C++ style

//  TEST_COUT << "Hello world" << std::endl;
}

TEST(pa_acq, Foo2)
{
// C style
// PRINTF("Hello world \n");

// or C++ style

//  TEST_COUT << "Hello world" << std::endl;
}

*/

/*
int main(int argc, char *argv[])
{
::testing::InitGoogleTest(&argc, argv);
RUN_ALL_TESTS();
//UME::SIMD::SIMDVec_f<float, 16>* f = new UME::SIMD::SIMDVec_f<float, 16>();
//size_t len = f->length();
//size_t len2 = vecCore::Mask_v<UME::SIMD::SIMDVec_f<float, 16> >::length();


return 0;
}
*/
