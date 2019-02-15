#include <cstddef> // size_t

struct String {
public:
	String(const char *str = "");
	String(size_t n, char c);
	~String();

    String(const String &other);
    String& operator=(const String &other);

	void append(const String &other);

	TmpString operator[] (int index)
	{
		return this;
	}
private:
	size_t size;
	char *str;
};

struct TmpString : String
{
	
};
