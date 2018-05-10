## This file is a template.  The comment below is emitted
## into the rendered file; feel free to edit this file.

// !!! WARNING: This is GENERATED Code... Please do NOT edit !!!

#include <map>
#include "conf.hpp"

std::map<int64_t, PIDConf> ZoneConfig = {
% for zone in PIDDict.iterkeys():
    % if zone:
    {${zone},
        {
            % for key, details in PIDDict[zone].iteritems():
            {"${key}",
                {"${details['type']}",
                 {
                   % for item in details['inputs'].split():
                   "${item}",
                   % endfor
                 },
                 <%
                      # If the PID type is a fan, set-point field is unused,
                      # so just use a default of 0.  If the PID is not a type
                      # of fan, require the set-point field.
                      if 'fan' == details['type']:
                          setpoint = 0
                      else:
                          setpoint = details['set-point']
                  %>
                 ${setpoint},
                 {${details['pid']['sampleperiod']},
                  ${details['pid']['p_coefficient']},
                  ${details['pid']['i_coefficient']},
                  ${details['pid']['ff_off_coefficient']},
                  ${details['pid']['ff_gain_coefficient']},
                  {${details['pid']['i_limit']['min']}, ${details['pid']['i_limit']['max']}},
                  {${details['pid']['out_limit']['min']}, ${details['pid']['out_limit']['max']}},
                  ${details['pid']['slew_neg']},
                  ${details['pid']['slew_pos']}},
                },
            },
            % endfor
        },
    },
   % endif
% endfor
};