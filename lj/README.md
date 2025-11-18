jbig support
============


`hp_encode_bits_to_jbig` is used for printer supported by
https://github.com/OpenPrinting/foo2zjs

foo2xqx support :

the HP LaserJet P1005/P1006/P1007/P1008,
the HP LaserJet P1505,
the HP LaserJet P2014,
the HP LaserJet M1005 MFP,
the HP LaserJet M1120 MFP,
the HP LaserJet Pro M1132s MFP,
the HP LaserJet Pro M1212nf MFP,

It use https://www.cl.cam.ac.uk/~mgk25/jbigkit/

options for jbigkit where taken from foo2xqx.c

HPJetReadyCompress
==================

`HPJetReadyCompress` is used for printer of tech-class=LJJetReady
These printer are supported by supported by https://hp-pxl-jetready.sourceforge.net/


    HP Color LaserJet 3500
    HP Color LaserJet 3550
    HP Color LaserJet 3600


see `i_compress_row`


build
=====

```
make lz
copy lz to the hp plugins dir /usr/share/hplip/prnt/plugins/
```

test
====

```
make test_lj
`LD_LIBRARY_PATH=. ./test_lj`
`DEVICE_URI=hp:test LD_LIBRARY_PATH=/usr/share/hplip/prnt/plugins/ ./test_lj`
```
