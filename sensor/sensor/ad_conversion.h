#ifndef AD_CONVERSION_H_
#define AD_CONVERSION_H_
/*
Set register to start a new AD conversion.
*/
void start_ad_conversion();

/*
Set the source of the next AD conversion

src - the source to use as input to the AD converter
*/
void set_ad_source(ad_source src);

/*
Convert the current input to the given AD source. Waits for the 
conversion to finish and returns the converted value.

src - the source to use as input to the AD converter

return - the analog vlalue converted to an int between 0 and 1024
*/
int convert_ad(ad_source src);

#endif /* AD_CONVERSION_H_ */