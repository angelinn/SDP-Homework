void BFS(r)
{
	if (!r)
		return;

	queue q;
	q.push(r);
	q.push(NULL);

	while (q.size() > 1)
	{
		node* e = q.pop();
		if (!e)
		{
			cout << endl;
			q.push(e);
		}
		else
		{
			cout << e->data;
			node* s = e->son;
			while (s)
			{
				q.push(s);
				s = s->next;
			}
		}
	}

}