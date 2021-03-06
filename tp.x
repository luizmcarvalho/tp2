const MAXPARAMNAME = 1000000;
typedef string name<MAXPARAMNAME>;

const MAXNAMELEN = 255; /* tamanho maximo do comando */
typedef string comando<MAXNAMELEN>; /* tipo comando */

struct tp_info {
	comando grep_args;
	name data;
};

program TP_PROG
{
	version TP_VERS
	{
		string TP_PROC(struct tp_info) = 1;
		void TP_EXIT(struct tp_info) = 2;
	} = 1;
} = 0x03071988;
