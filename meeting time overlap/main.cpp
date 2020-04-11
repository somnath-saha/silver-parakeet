//Meeting time problem
/*
Sample input:
[[9:00,10:30],[12:00,13:00],[16:00,18:00]]
[9:00,20:00]
[[10:00,11:30],[12:30,14:30],[14:30,15:00],[16:00,17:00]]
[10:00,18:30]
30

Sample output: [[11:30,12:00], [15:00,16:00], [18:00,18:30]]

24x60 = 1440 minutes
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class TimeInterval
{
    int startMin;
    int endMin;

public:
    TimeInterval(pair<string, string> p)
    { //[11:30,12:00]
        string beg = p.first;
        string end = p.second;
        int pos = beg.find(":");
        startMin = stoi(beg.substr(0, pos)) * 60;
        startMin += stoi(beg.substr(pos + 1));
        pos = end.find(":");
        endMin = stoi(end.substr(0, pos)) * 60;
        endMin += stoi(end.substr(pos + 1));
    }
    TimeInterval(int beg, int end)
    {
        startMin = beg;
        endMin = end;
    }
    bool isValid(int t) const
    {
        return ((endMin - startMin + 1) > t);
    }
    int getStartMin() const
    {
        return startMin;
    }
    int getEndMin() const
    {
        return endMin;
    }
    string to_string() const
    {
        string res = std::to_string((startMin / 60)) +
                     ":" + std::to_string(startMin % 60);
        res += ", " + std::to_string(endMin / 60) +
               ":" + std::to_string(endMin % 60);
        return res;
    }
};

class MeetingCalender
{
    vector<bool> v;
    vector<TimeInterval> res;
    bool changed;
    bool debug = true;
public:
    MeetingCalender() : v(vector<bool>(1440, false)), res(vector<TimeInterval>()), changed(false) {}

    void Init(TimeInterval t)
    {
        cout<<"Init:"<<endl;
        int begIndex = t.getStartMin();
        int endIndex = t.getEndMin();
        if(debug) cout<<"Setting "<<begIndex<<" to "<<endIndex<<endl;
        while (begIndex <= endIndex)
            v[begIndex++] = true;
    }
    void Print()
    {
        int n = v.size(), beg = -1, end = 0;
        for (int i = 0; i < n; ++i)
        {
            if (beg < 0 && v[i])
            {
                beg = i;
            }
            else if (beg > 0 && !v[i])
            {
                end = i;
                cout<<"("<<beg<<","<<end-1<<")"<<" ";
                beg = -1;
            }
        }
        cout<<endl;
    }
    void AddMeeting(TimeInterval t)
    {
        if(debug) cout<<"AddMeeting:"<<endl;
        int begIndex = t.getStartMin()+1;
        int endIndex = t.getEndMin()-1;
        if(debug) cout<<"Resetting "<<begIndex<<" to "<<endIndex<<endl;
        if((begIndex-1)>0 && v[begIndex-1] && !v[begIndex-2]) {
            begIndex = false;
        }
        while (begIndex <= endIndex)
            v[begIndex++] = false;
        changed = true;
        if(debug) Print();
    }
    const vector<TimeInterval> &GetAvailableTime()
    {
        if (changed)
        {
            int n = v.size(), beg = -1, end = 0;
            for (int i = 0; i < n; ++i)
            {
                if (beg < 0 && v[i])
                {
                    beg = i;
                }
                else if (beg > 0 && !v[i])
                {
                    end = i;
                    res.push_back(TimeInterval(beg, end));
                    beg = -1;
                }
            }
        }
        return res;
    }
    vector<TimeInterval> GetCombinedTimeIntervals(MeetingCalender m2)
    {
        MeetingCalender res;
        vector<TimeInterval> ti = m2.GetAvailableTime();
        for (auto &i : ti)
        {
            res.AddMeeting(i);
        }
        ti = GetAvailableTime();
        for (auto &i : ti)
        {
            res.AddMeeting(i);
        }
        return res.GetAvailableTime();
    }
};

string getAvailableTime(const vector<pair<string, string>> &vs1,
                        const vector<pair<string, string>> &vs2,
                        pair<string, string> &p1, pair<string, string> &p2, int interval)
{
    MeetingCalender m1, m2;
    m1.Init(TimeInterval(p1));
    m2.Init(TimeInterval(p2));
    for (const pair<string, string> &s : vs1)
    {
        m1.AddMeeting(TimeInterval(s));
    }
    for (const pair<string, string> &s : vs2)
    {
        m2.AddMeeting(TimeInterval(s));
    }
    vector<TimeInterval> res = m1.GetCombinedTimeIntervals(m2);
    string retVal;
    for (const auto &i : res)
    {
        if (i.isValid(interval))
        {
            retVal += i.to_string() + ", ";
        }
    }
    return retVal;
}

int main()
{
    vector<pair<string, string>> vs1({{"9:00", "10:30"}, {"12:00", "13:00"}, {"16:00", "18:00"}});
    vector<pair<string, string>> vs2({{"10:00", "11:30"}, {"12:30", "14:30"}, {"14:30", "15:00"}, {"16:00", "17:00"}});
    pair<string, string> p1({"9:00", "20:00"});
    pair<string, string> p2({"10:00", "18:30"});
    int interval = 130;
    cout << getAvailableTime(vs1, vs2, p1, p2, interval);
    TimeInterval t(p1), t2(p2);
    cout << t.to_string() << endl
         << t2.to_string();
    return 0;
}