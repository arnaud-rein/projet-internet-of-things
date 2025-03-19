#include "DisplayLatLng.hpp"

String DisplayLatLng(){
    String gnssData = get_GNSS_Info();
    String timeStamp = getTimeStamp(gnssData);
    Serial.println(convertTimestampToLocalTime(timeStamp, 1));
    return getLatLng(gnssData);
   
}