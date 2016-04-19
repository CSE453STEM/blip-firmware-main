struct data {
	char blip;
	char pay_size;
	char payload[];
};

struct data extract(char[] i) {
	if( i[0] == 0xFF ) {
		struct data ret;
		ret.blip = i[1];
		ret.pay_size = i[2];
		strncpy( ret.payload, &i[3], i[2]);
		ret.payload[i[2]] = '\0';
	}
};

int main(void) {
	char[] i = 0xFF1008AABBCCDDEEAABBCC;
	struct data p = extract(i);
	
}
