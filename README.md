H.264 Data Extractor
===============

This software extracts the hidden data which has been embedded into H.264 coded videos by <a target="_blank" href="https://github.com/mohghasem/DataHidingH264">Data Embedder</a>.

### Paper presenting video data hiding:
M. Ghasempour and M. Ghanbari, "A Low Complexity System for Multiple Data Embedding Into H.264 Coded Video Bit-Stream," in IEEE Transactions on Circuits and Systems for Video Technology, vol. 30, no. 11, pp. 4009-4019, Nov. 2020, [DOI: 10.1109/TCSVT.2019.2947545](https://doi.org/10.1109/TCSVT.2019.2947545)

- [Build](#build)
- [Usage](#usage)
- [Copyright](#copyright)
- [References](#references)

Build
----------------------------------------------

1. You will need to check [JM repository](https://vcgit.hhi.fraunhofer.de/jvet/JM) to see how to build the project.

Usage
----------------------------------------------
```
./ldecod (or ldecod.exe on Windows) [-d JM_CONFIG_FILE] [-MD OUTPUT_TEXT_FILE] [-ID DATA_ID]
```
- **JM_CONFIG_FILE**: The original config file for H.264/AVC JM reference software
- **OUTPUT_TEXT_FILE**: The path and name of output file. The extracted data will be written on this file.
- **DATA_ID**: The ID of embedded data that you want to extract. In case of single data insertion, it should set to 0.

Example:
```
./ldecod -d decoder.cfg -MD out.txt -ID 0
```


Copyright
----------------------------------------------
Permission is hereby granted, without written agreement and without license or royalty fees, to use, copy, modify, and distribute the software provided and its documentation for research purpose only, provided that this copyright notice and the original authors' names appear on all copies and supporting documentation. The software provided may not be commercially distributed.

References
----------------------------------------------
- T. Wiegand, G. J. Sullivan, G. Bjontegaard and A. Luthra, “Overview of the H.264/AVC video coding standard,” IEEE Transactions on Circuits and Systems for Video Technology, 13(7), 560–576, 2003.
- M. Fallahpour, S. Shirmohammadi, M. Ghanbari, “A high capacity data hiding algorithm for H.264/AVC video,” Security and Communication Networks, 8(16), 2947-2955, 2015.
