/***
*        解析csv文件
*/
BOOL ParseCSVFile(string fileName)
{
    //文件名错误
    vector<string> fields; //声明一个字符串向量
    string field;
    SplitString(fileName.c_str,fields,".");
    if (fields.size() < 2 || fields[fields.size()-1] != "csv")
    {
        //"文件格式错误";
    }

    ifstream fin(fileName); //打开文件流操作
    string line;
    int lineCount = 0;
    while (getline(fin, line))   //整行读取，换行符“\n”区分，遇到文件尾标志eof终止读取
    {
        vector<string> fields; //声明一个字符串向量
        string field;
        SplitString(line,fields,",");
        if (fields.size() != 7)
        {
            continue;
        }
        string loginName = Trim(fields[0]); //用户登录名
        string userName = Trim(fields[1]); //用户名称
        string cardId = Trim(fields[2]); //身份证号
        string sex = Trim(fields[3]);    //性别
        string ustatus = Trim(fields[4]); //状态
        string invalidTime = TimeToDbTime(Trim(fields[5])); //到期时间
        string department = Trim(fields[6]); //所属部分信息
        if (lineCount == 0)
        {
            lineCount++;
            continue;
        }

        lineCount++;

        //具体处理方法。。。
    }

    return TRUE;
}

/***
*        按指定字符截取字符串
*/
void SplitString(const string& str, vector<string>& ret_, const string &sep)
{
    if (str.empty())
    {
        return ;
    }

    string tmp;
    string::size_type pos_begin = 0;//str.find_first_not_of(sep);
    string::size_type comma_pos = 0;

    while (pos_begin != string::npos)
    {
        comma_pos = str.find(sep, pos_begin);
        if (comma_pos != string::npos)
        {
            tmp = str.substr(pos_begin, comma_pos - pos_begin);
            pos_begin = comma_pos + sep.length();
        }
        else
        {
            tmp = str.substr(pos_begin);
            pos_begin = comma_pos;
        }

        ret_.push_back(tmp);
    }
}

/***
*        删除字符串中空格，制表符tab等无效字符
*/
string Trim(string& str)
{
    str.erase(0,str.find_first_not_of(" \t\r\n"));
    str.erase(str.find_last_not_of(" \t\r\n") + 1);
    return str;
}
