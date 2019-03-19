#!/QOpenSys/usr/bin/bash
    # converting theory
    #1. system "cpytostmf frommbr('/QSYS.LIB/CMB000PDN1.LIB/QCPPSRC.FILE/SQLSTMTBSE.MBR') tostmf('/home/pcheng/sqlstmtbse1.cpp') stmfopt(*REPLACE) STMFC
    #CSID(*STDASCII) ENDLINFMT(*LF)"
    #2. system "qsh cmd('cat /QSYS.LIB/TAM000PDN1.LIB/QCPPSRC.FILE/ACKMGR.MBR')" > ACKMGR.cpp
    #this way could not correctly handle end of line
    #3. "system" is used to run CL command
    #example commamd string:
    #./cpmbr.sh CMB000PDN1 CPP COMMBASE ,  you will copy file from /QSYS.LIB/CMB000PDN1.LIB/QCPPSRC.FILE/*.MBR into COMMBASE dir

    #
    # Syponosis
    # copy source file member to IFS
    # 
    #
    baselibrary="$1"
    echo source database library: $baselibrary
    physical="$2"
    echo file type: $physical
    destination="$3"
    echo copy to: $destination
    basedir="/QSYS.LIB/${baselibrary}.LIB/Q${physical}SRC.FILE"
    ext="${physical,,}"
    curdir=`pwd`
    for entry in "$basedir"/*
    do
        filename=${entry%.*}
        filename=${filename##*/}
        echo "copying $entry to $curdir/$destination/$filename.$ext"
        #system "qsh cmd('cat $entry')" > $destination/$filename.$ext
        system "cpytostmf frommbr('$entry') tostmf('$destination/$filename.$ext') stmfopt(*REPLACE) STMFCCSID(*STDASCII) ENDLINFMT(*LF)"
    done