# include "t..c"
 /* tr.c: number register allocation */
char * nregs[] ={
	/* this array must have at least 3*qcol entries
	   or illegal register names will result */
	"4a","4b","4c","4d","4e","4f","4g","4h","4i","4j",
	"4k","4l","4m","4n","4o","4p","4q","4r","4s","4t",
	"5a","5b","5c","5d","5e","5f","5g","5h","5i","5j",
	"5k","5l","5m","5n","5o","5p","5q","5r","5s","5t",
	"6a","6b","6c","6d","6e","6f","6g","6h","6i","6j",
	"6k","6l","6m","6n","6o","6p","6q","6r","6s","6t",
	"7a","7b","7c","7d","7e","7f","7g","7h","7i","7j",
	"7k","7l","7m","7n","7o","7p","7q","7r","7s","7t",
	"8a","8b","8c","8d","8e","8f","8g","8h","8i","8j",
	"8k","8l","8m","8n","8o","8p","8q","8r","8s","8t",
	"9a","9b","9c","9d","9e","9f","9g","9h","9i","9j",
	"9k","9l","9m","9n","9o","9p","9q","9r","9s","9t",
	0};
char *
reg(col, place)
{
if(sizeof(nregs) < 2*3*qcol)
	error("Too many columns for registers");
return (nregs[qcol*place+col]);
}
