#include "result.h"

bool GreaterSort(Result a, Result b) {
	return (a.match > b.match || (a.match == b.match && a.word.length() < b.word.length()));
}