#include <glib.h>
static GMutex *mutex = NULL;
static gboolean t1_end = FALSE;
static gboolean t2_end = FALSE;
typedef struct _Arg Arg;
struct _Arg
{
	GMainLoop* loop;
	gint max;
};
void	run_1(Arg *arg)
{
	int i ;

	for(i=0; i<arg->max; i++)
	{
		if(g_mutex_trylock(mutex) == FALSE)
		{
			g_print("%d : thread 2 locked the mutex \n", i);
			g_print("%d ���߳�2������ ����\n", i);
			g_mutex_unlock(mutex);
		}
		else
		{
			g_usleep(10);
		}
	}
	t1_end = TRUE;
}
void	run_2(Arg *arg)
{
	int i;
	for(i=0; i<arg->max; i++)
	{
		if(g_mutex_trylock(mutex) == FALSE)
		{
			//g_print("%d : thread 1 locked mutex \n", i);
			g_print("%d ���߳�1�����˻������\n", i);
			g_mutex_unlock(mutex);
		}
		else
		{
			g_usleep(10);
		}
	}
	t2_end = TRUE;
}
void run_3(Arg *arg)
{
	for(;;)
	{
		if(t1_end && t2_end)
		{
			g_main_loop_quit(arg->loop);
			break;
		}
	}
}
int	main(int argc, char *argv[])
{
	GMainLoop *mloop;
	Arg *arg;

	if(!g_thread_supported())
		g_thread_init(NULL);
	mloop = g_main_loop_new(NULL, FALSE);

	arg = g_new(Arg, 1);
	arg->loop = mloop;
	arg->max = 11;

	mutex = g_mutex_new();
	g_thread_create(run_1, arg, TRUE, NULL);
	g_thread_create(run_2, arg, TRUE, NULL);
	g_thread_create(run_3, arg, TRUE, NULL);

	g_main_loop_run(mloop);
	g_print("�߳�3�˳��¼�ѭ��\n");
	g_mutex_free(mutex);
	g_print("�ͷŻ������\n"); 
	g_free(arg);
	g_print("end of game\n");
}
