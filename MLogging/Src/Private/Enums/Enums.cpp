
#include <MLoggingPCH.h>
#include <Enums/Enums.h>

std::ostream& operator<<(std::ostream& os, MLog::Level lvl) {
std::string s("");

switch (lvl) {
case MLog::Level::Information:
	s = "Information";
	break;
case MLog::Level::Warning:
	s = "Warning";
	break;
case MLog::Level::Error:
	s = "Error";
	break;
}
os.write(s.c_str(), s.size());

return os;
}