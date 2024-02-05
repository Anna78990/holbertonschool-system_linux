

char *handle_get(int cs)
{
	char buffer[BUF_SIZE], header[BUFFER_SIZE];
	char *ok = "HTTP/1.1 200 OK\r\n", *length = "Content-Length: ";
	char *json = "Content-Type: application/json\r\n\r\n";
	char *id = "\"id\"", *t = "\"title\"", *desc = "\"description\"";
	struct todo_t *todo = root;

	memset(buffer, 0, BUFFER_SIZE), memset(header, 0, BUFFER_SIZE);
	buffer[0] = '[';
	while (todo)
	{
		sprintf(buffer + strlen(buffer),
			"{%s:%d, %s:\"%s\",%s:\"%s\"}", id, todo->id, t,
			todo->title, desc, todo->description);
		if (todo->next)
			buffer[strlen(buffer)] = ',';
		todo = todo->next;
	}
	buffer[strlen(buffer)] = ']';
	sprintf(header, "%s%s%lu\r\n%s%s", ok, length, strlen(buffer), json, buffer);
	send(cs, header, strlen(header), 0);
	res_check(header);
	return (NULL);
}
