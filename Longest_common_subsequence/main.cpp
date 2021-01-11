#include"include.h"
#include"class.h"
#include"func.h"

void main() {
	Bio_seq a("ABCBDABCABCABCACB");
	Bio_seq b("BDCABABABBACABABCA");
	Longest_common_sequence(a, b);
}