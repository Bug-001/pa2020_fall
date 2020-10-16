#include "trap.h"

#define status_num 1 << 5

char* moon_cakes[10] = {
	"efqfiqefuihqoiwefidsbf",
	"awfafadfkhfkajdf",
	"awhlefhalkwfalkjfcvavbdslkvbawieuhfwipaeufgbuabvdaslkvbasdbvakjdefefaefaefhaeefaefhaefhalkwehfalwkjefkdlbvaklsdbvlakbdvabsdjklvbalkbdsvjkabsdvbakehfauhwefaluwhefaiwlvdbklsdbvalwhefiuavbkljsdvbalkdvakjsbdvklsdbva",
	"aefawelkfhakefhdjbvaguhlijnkbhgvftcrdfyguhijnbvcxdetrfgyhujmknbvcfdrtgyhujikmnbdfygbjhcxgdrytfugifcdyxrtufgihbfcdxtfuygicxydtufytgijhxdctfygubvfcdxtfyguvfcdxtfycdxswredtrszesrdetfycfyguhbkghuijhjbkijnhbkjguhbvjygjvchtfvcdxrcxsrdrszxrdsrdtcfdxctfvygjyfgubhgvbhnlbkhlngkvbkhjgvfgbkvjfcd",
	"fawefwedsvuggggggghbfvgauhvvbfawivnhbwaidnvhdfhwednhbfwadnvbfhwadnvfhdvnfbhanvfbhnadbh",
	"rfbawhvbwdanhvbfwdanhfbwahkbfewafhyubewnjlfibhewjdfhebwafihebwkidfhyeuwbhadihfsubewnadhbewandfivhbewandfhbweabewhandhbweandhbewajfhbejahfbewhanfhbhanvhbhahygawhebfihywhebafueshhbewnefhbewnjafhebhewnajfhbewjafnsbhewnsbhewans",
	"bfeyhbasduyawbfehbdurhydreegfnilbreknfjvdhizjdhigejofuhaeginugnfognjfognjbfsgnfjirgnafrugehfibvnjrgenbjvmfkaesbnfkvjmajgebnaflvjjebsfvnjaebfhkvnwdmjafevwldmkajfebvknjhblvnjefbhflknwavfbehknvjfafjenhbkavnwjfekwnjvabfhkdjafebhknwajdnjkd",
	"ogiuhlkjgrljeshkgudzghlejbzhagrjzdphuaegjibuhajkref;zbjkgnfohubakihubrjwnlfbjhaergfdhrbakjfldhifwkjvzdhulkawfjvzduhjefhudslejbhdfgsefjdihusejfhugeanjfbsdhbusfji;hsljnafbhsenjfbhslfjeknbhsjnefsdhsfejbdhusf",
	"njununujjnujnjnjujnjnjnujnjnjnjnnjnjjn",
	"jucsnjusnucsjcusjcusjcdsdcdsnccjsdncsnicsnscjncscnsjcdicjusjcnhususjcunjscusncshun",
};

int ans[10] = {10, 13, 188, 241, 77, 193, 140, 188, 38, 76};

int main(){
	int i = 0;
	for(i = 0; i < 10; ++i){
		int total = 0;
		int pos[status_num];
		int j = 0;
		for (j = 0; j < status_num; ++j){
			pos[j] = -2;
		}
		int status = 0;
		pos[status] = -1;
		// start = 0;
		int end = 0;
		for (end = 0; end < 10000; ++end){
			if(moon_cakes[i][end] == 0) break;
			switch (moon_cakes[i][end]){
			case 'n':
				status ^= 1 << 4;
				break;
			case 'j':
				status ^= 1 << 3;
				break;
			case 'u':
				status ^= 1 << 2;
				break;
			case 'c':
				status ^= 1 << 1;
				break;
			case 's':
				status ^= 1 << 0;
				break;
			}
			if (pos[status] == -2){
				pos[status] = end;
			}
			else{
				int temp = end - pos[status];
				total = temp > total ? temp : total;
			}
		}
		nemu_assert(total == ans[i]);
	}
	return 0;
}