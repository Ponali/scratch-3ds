typedef struct Block{
	int id;
	float x;
	float y;
	struct Block *after;
	bool hasAfter;
};