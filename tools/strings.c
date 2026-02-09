size_t count_lines_file(FILE *p_file)
{
    size_t line_n = 0;
    size_t char_count;
    char c;

    fseek(p_file, 0, SEEK_SET);

    while(!feof(p_file))
    {
        c = fgetc(p_file);

        if (c == '\n')
        {
            if (char_count > 1) // Only if there's something in this line
            {
                line_n++;
            }

            char_count = 0;
            continue;
        }

        if (c == EOF && char_count > 0) // If there's no '/n' on the last line
        {
            line_n++;
            break;
        }
        
        char_count++;
    }

    fseek(p_file, 0, SEEK_SET);

    return line_n;
}
