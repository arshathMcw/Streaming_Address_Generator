## Streaming Address Generator
```
The Streaming Address generator (SA) is a multi-dimension offset computation engine. Computing multi-dimension offsets in deeply nested loops cost CPU cycles. C7x offers upto four address generators namely SA0, SA1, SA2, SA3 to compute offsets upto 6D. The SA can be used in conjunction with load/store instructions. Programming SA is similar to programming an SE. The difference here is that SA provides only address offsets whereas SE provides the actual data.


strm_agen<<SA Idx>, <vector_type>>::get(<base_address>) //Returns address
*strm_agen<<SA Idx>, <vector_type>>::get(<base_address>) //Returns value


```
