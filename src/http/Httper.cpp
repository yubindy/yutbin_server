#include "../../include/Httper.hpp"
using namespace yb;
using namespace yb::http;
//对于http做简单解析
const char *Httpline::httpstringmethod[DONT_UNDERSTAND] = {
    "GET", "POST" /* , "HEAD", "PUT", "PATCH", "DELETE", "TRACE", "CONNECT", */
};
void Httpline::debug()
{
    LOG(lev::DEBUG) << "RequestLine: " << endl;
    LOG(lev::DEBUG) << "version_: " << version << " url_: " << url
                    << " method: " << getstringmethod() << endl;
}
void Httper::requestline()
{
    int len;
    for (pt = 0; pt != len; pt++)
    {
        if (buf[pt] != '\r')
            continue;
        if (buf[pt + 1] == '\n')
            break;
    }
    if (strncmp(buf + pt, CR_LF, 2) != 0) //不完整
        return;
    m_end = pt + 2;
    pt = m_beg;
    len = m_end - m_beg;
    request->line.setnow(Httpline::linestate::method_);

    if (len >= strlen("GET") && strncmp(buf + pt, "GET", strlen("GET")) == 0)
    {
        request->line.setmethod(GET);
        pt += strlen("GET");
    }
    else if (len >= strlen("POST") && strncmp(buf + pt, "POST", strlen("POST")) == 0)
    {
        request->line.setmethod(POST);
        pt += strlen("POST");
    }
    else
    {
        line = linefail;
    }
    for (; pt != m_end; pt++)
    {
        if (pt == m_end)
            break;
        else if (buf[pt++] != ' ')
            break;
    }
    request->line.setnow(Httpline::linestate::url_);
    int u_beg = pt;
    while (pt != m_end && buf[pt++] != ' ')
    {
    }
    request->line.seturl(std::string(buf + u_beg, pt - u_beg - 1));
    LOG(lev::DEBUG) << buf[u_beg] << pt - u_beg << endl;
    request->line.setnow(Httpline::linestate::version_);
    if (!strncmp(buf + pt, "HTTP/1.1", 8) ||
        !strncmp(buf + pt, "HTTP/1.0", 8))
    {
        request->line.setversion(std::string(buf + pt, 8));
        pt = m_end;
        line = linesuccess;
        return;
    }
    line = linefail;
}
void Httper::requesthead()
{
    m_beg = m_end;
    linestate lt = linecontinue;
    for (pt = m_end; pt != len; pt++)
    {
        while (pt != len && buf[pt++] != '\r' && buf[pt] != '\n')
        {
        }
        m_end = pt;
        pt = m_beg;
        while (buf[pt++] != ' ')
        {
        }
        request->head.add(std::string(m_beg, pt - m_beg - 1), std::string(pt, m_end));
        if (strncmp(buf + pt+1, CR_LF, 2) == 0)
        {
            lt = linesuccess;
            break;
        }
    }
    pt = m_end + 1;
    if (lt == linesuccess)
        line = linesuccess;
    else
        line = linefail;
    return;
}
void Httper::requestmessage(int len_)
{
    while (pt != len && buf[pt++] != '\r' && buf[pt] != '\n')
    {
    }
    if (pt + len_ > len)
    {
        line = linecontinue;
    }
    else
    {
        request->message.setmessage(std::string(buf + pt, len_));
        line = linesuccess;
    }
    return;
}
Httper::totalstate Httper::requestall()
{
    requestline();
    if (line = linefail)
    {
        end = fail;
        return end;
    }
    requesthead();
    if (line = linefail)
    {
        end = fail; // 404
        return end;
    }
    if (request->line.getmethod() == GET)
    {
        end = success;
        httpersize = pt;
        return end;
    }
    auto kv = request->head.get("Content-Length");
    if (request->line.getmethod() == POST && !kv.first.empty() && pt < len)
    {
        int lines = std::stoi(kv.second);
        if (lines > 0)
        {
            requestmessage(lines);
            if (line == linefail)
            {
                end = fail;
                LOG(lev::DEBUG) << "Something we can't understand now" << endl;
            }
            else if (line = linecontinue)
            {
                end = continues;
                LOG(lev::DEBUG) << "Incomplete Request Body, continue Waiting..." << endl;
            }
            else
            {
                end = success;
            }
        }
    }
    return end;
}
