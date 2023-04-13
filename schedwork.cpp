#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool createSchedule(size_t hor, size_t ver, size_t list, size_t required, vector<size_t> move, 
	            const AvailabilityMatrix& avail, DailySchedule& sched);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();

    // Add your code below

    vector<size_t> move(avail[0].size());fill(move.begin(),move.end(),0);

    // make sched

    vector<Worker_T> workersVect(dailyNeed);
	DailySchedule curr(avail.size(), workersVect);
    bool fin =createSchedule(size_t{},size_t{},maxShifts,dailyNeed,move,avail,curr);
	sched =curr;
	return fin;
}

bool createSchedule(size_t hor, size_t ver, size_t list, size_t required, vector<size_t> move, 
	            const AvailabilityMatrix& avail, DailySchedule& sched){
	if(avail.size()==hor) {
        return true;
    }
    else{
        bool found = false;
        for (size_t j=0; avail[0].size()>j; j++) {
            if (avail[hor][j]==1 && list!=move[j]) {
                sched[hor][ver]=j;
                move[j]=move[j]+1;
                
                const size_t vertical_count=sched[0].size();
                size_t clength=(ver+1)%vertical_count;
                size_t hlength =hor+(ver+1)/vertical_count;
                found =createSchedule(hlength,clength,list,required,move,avail,sched);
                if(found){
                    return true;
                }
                else{
                    move[j]--;
                    sched[hor][ver]=0;
                }
            }
        }
        return found;
    }
    return false;
}