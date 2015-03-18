# How to Enable AXI Burst Feature without Other AXI MM Features in Custom IP #

## Background ##
In some cases, custom IP requires the burst feature of Full Featured AXI Interface, but other features like reordering or multiple outstanding issuing features are not required.

## Implemenatation Idea ##
Pull down AWREADY and ARREADY as soon as the custom IP receives an AXI transaction request. Pull these signals up after the data transfer in BRESP and RDATA completes.

In this case, if there are simutanous transaction requests from AW channel or AR channel, the latter ones will be held until the first one is serviced, while data channel can still utilize the burst feature of Full Featured AXI Interface.
