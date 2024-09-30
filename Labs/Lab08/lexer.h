#include <unordered_map>
#include <string>
#include <sstream>
using std::stringstream;
using std::unordered_map;
using std::string;

// cada token possui uma tag (número a partir de 256)
// a tag de caracteres individuais é seu código ASCII
enum Tag { TYPE = 256, INT, FLOAT, ID };

// classes para representar tokens
struct Token
{
	int tag;
	Token() : tag(0) {}
	Token(int t) : tag(t) {}
	virtual string toString() { stringstream ss; ss << char(tag); return ss.str(); }
};

struct Int : public Token
{
	int value;
	Int(): Token(Tag::INT), value(0) {}
	Int(int v) : Token(Tag::INT), value(v) {}
	virtual string toString() { stringstream ss; ss << value; return ss.str(); }
};

struct Float : public Token
{
	float value;
	Float(): Token(Tag::FLOAT), value(0) {}
	Float(float v) : Token(Tag::FLOAT), value(v) {}
	virtual string toString() { stringstream ss; ss << value; return ss.str(); }
};

struct Id : public Token
{
	string name;
	Id(): Token(Tag::ID) {}
	Id(int t, string s) : Token(t), name(s) {}
	virtual string toString() { return name; }
};

// analisador léxico
class Lexer
{
private:
	// tipos de token da linguagem
	struct
	{
		Token t;
		Float f;
		Int i;
		Id id;
	}
	token;
	
	int line = 1;
	char peek;
	unordered_map<string, Id> id_table;

public:
	Lexer();
	int Lineno();
	Token * Scan();
};
