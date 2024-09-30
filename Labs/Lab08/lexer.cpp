#include "lexer.h"
#include <fstream>
#include <sstream>
using std::stringstream;

extern std::ifstream fin;

// construtor
Lexer::Lexer()
{
	// insere palavras-reservadas na tabela de id's
	id_table["int"] = Id{Tag::TYPE, "int"};
	id_table["char"] = Id{Tag::TYPE, "char"};
	id_table["bool"] = Id{Tag::TYPE, "bool"};
	id_table["float"] = Id{Tag::TYPE, "float"};

	// inicia leitura da entrada
	peek = fin.get();
}

// retorna número da linha atual
int Lexer::Lineno()
{
	return line;
}

// retorna tokens para o analisador sintático
Token *Lexer::Scan()
{
	// ignora espaços em branco, tabulações e novas linhas
	while (isspace(peek))
	{
		if (peek == '\n')
			line += 1;
		peek = fin.get();
	}

	// retorna números
	if (isdigit(peek))
	{
		int n, i = 0, v = 0;

		do
		{
			// converte caractere 'n' para o dígito numérico n
			n = peek - '0';
			v = 10 * v + n;
			peek = fin.get();
			if (i)
				i++;
			else if (peek == '.')
			{
				i = 1;
				peek = fin.get();
			}
		} while (isdigit(peek));

		if (i)
		{
			float vf = (float)v;
			for (; i > 1; i--)
			{
				vf /= 10;
			}

			// retorna o token FLOAT
			token.f = Float{vf};
			return &token.f;
		}

		// retorna o token INT
		token.i = Int{v};
		return &token.i;
	}

	// retorna palavras-chave e identificadores
	if (isalpha(peek))
	{
		stringstream ss;
		do
		{
			ss << peek;
			peek = fin.get();
		} while (isalpha(peek));

		string s = ss.str();
		auto pos = id_table.find(s);

		// se o lexema já está na tabela
		if (pos != id_table.end())
		{
			// retorna o token associado
			token.id = pos->second;
			return &token.id;
		}

		// se o lexema ainda não está na tabela
		Id new_id{Tag::ID, s};
		id_table[s] = new_id;

		// retorna o token ID
		token.id = new_id;
		return &token.id;
	}

	// operadores (e caracteres não alfanuméricos isolados)
	Token op{peek};
	peek = ' ';

	// retorna o token
	token.t = op;
	return &token.t;
}
