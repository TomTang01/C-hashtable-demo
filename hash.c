extern unsigned long hash_asm(unsigned long, unsigned long);

unsigned long hash(char *str) {
	unsigned long hash = 5381;
	unsigned int c;
	while ((c = (unsigned char) *str++) != '\0') {
		//hash = hash_asm((unsigned long) c, hash);
		hash = (hash << 5) + hash + c;
		// comment out one of the lines above depending on
		// whether you want to call the assembly function
		// or use the C code
	}
	return hash;
}
