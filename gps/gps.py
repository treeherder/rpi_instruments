import serial
ser_con = serial.Serial("/dev/ttyAMA0", 4800)

def parse_nmea(token):
  lines= ser_con.readline()
  line = lines.split("\r\n")
  for sentence in line:
    words = sentence.split(",")
    for word in words:
      if token in word:
        return sentence
        
def parse_GPGGA(sentence):
  key_list = ["type", "utc", "latitude", "n_s", "longitude", "e_w", "quality", "num_sats", "dilution", "altitude", "a_unit", "geoidal_separation", "g_unit", "age", "checksum"]
  d_key_list = ["type", "utc", "latitude", "n_s", "longitude", "e_w", "quality", "num_sats", "dilution", "altitude", "a_unit", "geoidal_separation", "g_unit", "age", "diff_id", "checksum"]
  #d_key is in case we have differential signal value field
  value_list = []
  if(sentence):
    values = sentence.split(",")
    for value in values:
      value_list.append(value)
    if (len(value_list) == 15):
      ret = dict(zip(key_list, value_list))
    elif (len(value_list) == 16):
      ret = dict(zip(d_key_list, value_list)) # there is a differential value    return ret
    return ret
    #   basically if it's not at least 15, we don't want it

def controller(in_pt):
  if(in_pt):
    print in_pt["longitude"],
    print in_pt["latitude"]
    
while True:
  controller(parse_GPGGA(parse_nmea("$GPGGA")))
