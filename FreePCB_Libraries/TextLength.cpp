//---------------------------------------------------------------------------


#pragma hdrstop

#include "TextLength.h"
#include "ABClibrary.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)



long TextLength (AnsiString Text)
	{
	long Length = 0;
	long i = 1;
	while (i <= Text.Length())
		{
		if (Text.SubString(i,1) == "A")		Length += 729000;
		else if (Text.SubString(i,1) == "a")	Length += 546000;
		else if (Text.SubString(i,1) == "B")	Length += 635000;
		else if (Text.SubString(i,1) == "b")	Length += 544000;
		else if (Text.SubString(i,1) == "C")	Length += 683000;
		else if (Text.SubString(i,1) == "c")	Length += 546000;
		else if (Text.SubString(i,1) == "D")	Length += 638000;
		else if (Text.SubString(i,1) == "d")	Length += 544000;
		else if (Text.SubString(i,1) == "E")	Length += 589000;
		else if (Text.SubString(i,1) == "e")	Length += 546000;
		else if (Text.SubString(i,1) == "F")	Length += 592000;
		else if (Text.SubString(i,1) == "f")	Length += 363000;
		else if (Text.SubString(i,1) == "G")	Length += 683000;
		else if (Text.SubString(i,1) == "g")	Length += 546000;
		else if (Text.SubString(i,1) == "H")	Length += 638000;
		else if (Text.SubString(i,1) == "h")	Length += 500000;
		else if (Text.SubString(i,1) == "I")	Length += 0;
		else if (Text.SubString(i,1) == "i")	Length += 91000;
		else if (Text.SubString(i,1) == "J")	Length += 455000;
		else if (Text.SubString(i,1) == "j")	Length += 272000;
		else if (Text.SubString(i,1) == "K")	Length += 635000;
		else if (Text.SubString(i,1) == "k")	Length += 500000;
		else if (Text.SubString(i,1) == "L")	Length += 546000;
		else if (Text.SubString(i,1) == "l")	Length += 0;
		else if (Text.SubString(i,1) == "M")	Length += 729000;
		else if (Text.SubString(i,1) == "m")	Length += 1000000;
		else if (Text.SubString(i,1) == "N")	Length += 635000;
		else if (Text.SubString(i,1) == "n")	Length += 500000;
		else if (Text.SubString(i,1) == "O")	Length += 729000;
		else if (Text.SubString(i,1) == "o")	Length += 592000;
		else if (Text.SubString(i,1) == "P")	Length += 635000;
		else if (Text.SubString(i,1) == "p")	Length += 546000;
		else if (Text.SubString(i,1) == "Q")	Length += 729000;
		else if (Text.SubString(i,1) == "q")	Length += 546000;
		else if (Text.SubString(i,1) == "R")	Length += 635000;
		else if (Text.SubString(i,1) == "r")	Length += 366000;
		else if (Text.SubString(i,1) == "S")	Length += 635000;
		else if (Text.SubString(i,1) == "s")	Length += 498000;
		else if (Text.SubString(i,1) == "T")	Length += 635000;
		else if (Text.SubString(i,1) == "t")	Length += 363000;
		else if (Text.SubString(i,1) == "U")	Length += 635000;
		else if (Text.SubString(i,1) == "u")	Length += 500000;
		else if (Text.SubString(i,1) == "V")	Length += 729000;
		else if (Text.SubString(i,1) == "v")	Length += 546000;
		else if (Text.SubString(i,1) == "W")	Length += 909000;
		else if (Text.SubString(i,1) == "w")	Length += 726000;
		else if (Text.SubString(i,1) == "X")	Length += 638000;
		else if (Text.SubString(i,1) == "x")	Length += 500000;
		else if (Text.SubString(i,1) == "Y")	Length += 726000;
		else if (Text.SubString(i,1) == "y")	Length += 546000;
		else if (Text.SubString(i,1) == "Z")	Length += 638000;
		else if (Text.SubString(i,1) == "z")	Length += 500000;
		else if (Text.SubString(i,1) == "1")	Length += 229000;
		else if (Text.SubString(i,1) == "2")	Length += 638000;
		else if (Text.SubString(i,1) == "3")	Length += 635000;
		else if (Text.SubString(i,1) == "4")	Length += 681000;
		else if (Text.SubString(i,1) == "5")	Length += 638000;
		else if (Text.SubString(i,1) == "6")	Length += 589000;
		else if (Text.SubString(i,1) == "7")	Length += 635000;
		else if (Text.SubString(i,1) == "8")	Length += 638000;
		else if (Text.SubString(i,1) == "9")	Length += 592000;
		else if (Text.SubString(i,1) == "0")	Length += 635000;
		else if (Text.SubString(i,1) == "!")	Length += 89000;
		else if (Text.SubString(i,1) == "@")	Length += 955000;
		else if (Text.SubString(i,1) == "#")	Length += 683000;
		else if (Text.SubString(i,1) == "$")	Length += 638000;
		else if (Text.SubString(i,1) == "%")	Length += 818000;
		else if (Text.SubString(i,1) == "^")	Length += 726000;
		else if (Text.SubString(i,1) == "&")	Length += 907000;
		else if (Text.SubString(i,1) == "*")	Length += 455000;
		else if (Text.SubString(i,1) == "(")	Length += 319000;
		else if (Text.SubString(i,1) == ")")	Length += 319000;
		else if (Text.SubString(i,1) == "[")	Length += 319000;
		else if (Text.SubString(i,1) == "]")	Length += 319000;
		else if (Text.SubString(i,1) == "]")	Length += 319000;
		else if (Text.SubString(i,1) == "\\")	Length += 638000;
		else if (Text.SubString(i,1) == "|")	Length += 0;
		else if (Text.SubString(i,1) == "/")	Length += 818000;
		else if (Text.SubString(i,1) == "<")	Length += 729000;
		else if (Text.SubString(i,1) == ">")	Length += 729000;
		else if (Text.SubString(i,1) == "?")	Length += 546000;
		else if (Text.SubString(i,1) == ",")	Length += 91000;
		else if (Text.SubString(i,1) == ".")	Length += 91000;
		//
		if (i != Text.Length())			Length += 363000;
		i++;
		}
	return Length;
	}