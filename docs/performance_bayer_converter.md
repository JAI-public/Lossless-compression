# Conversion time with eBUS SDK PvBufferConverter

At lower pixel counts, the Bayerfilter makes little difference. At higher pixel counts, it can be effective up to about 8 threads.  

**Processing Time Unit: seconds**  

## SetBayerFilterSimple
PixelFormat = BayerRG8

### Width=1024, Height=1024
|   |ThreadNum=1   |ThreadNum=4 |ThreadNum=8|ThreadNum=16
|--|--|--|--|--|
|1  |0.00173 |0.0031|0.00472|0.0103
|2  |0.00166|0.0031|0.00474|0.0108
|3  |0.00162|0.0031|0.00501|0.0105

### Width=3072, Height=3072
|   |ThreadNum=1   |ThreadNum=4 |ThreadNum=8|ThreadNum=16
|--|--|--|--|--|
|1  |0.0142|0.0073 |0.00866|0.0119
|2  |0.0141|0.00733|0.00913|0.0134
|3  |0.0141|0.00722|0.00968|0.0127

### Width=5120, Height=5120
|   |ThreadNum=1   |ThreadNum=4 |ThreadNum=8|ThreadNum=16
|--|--|--|--|--|
|1  |0.043|0.019 |0.0154|0.0166
|2  |0.045|0.0196|0.0168|0.0172
|3  |0.0461|0.0184|0.0183|0.0171

## SetBayerFilter3x3

### Width=1024, Height=1024
|   |ThreadNum=1   |ThreadNum=4 |ThreadNum=8|ThreadNum=16
|--|--|--|--|--|
|1  |0.00599 |0.0041|0.00575|0.011
|2  |0.0031|0.004|0.0051|0.0111
|3  |0.0054|0.0041|0.00567|0.0104

### Width=3072, Height=3072
|   |ThreadNum=1   |ThreadNum=4 |ThreadNum=8|ThreadNum=16
|--|--|--|--|--|
|1  |0.0485|0.0208 |0.0139|0.0149
|2  |0.0492|0.0151|0.0143|0.0153
|3  |0.0484|0.0157|0.0129|0.0205

### Width=5120, Height=5120
|   |ThreadNum=1   |ThreadNum=4 |ThreadNum=8|ThreadNum=16
|--|--|--|--|--|
|1  |0.141|0.0408|0.0297|0.0251
|2  |0.155|0.038|0.0286|0.0255
|3  |0.137|0.0463|0.0302|0.0248

