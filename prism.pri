unix: {
isEmpty(PREFIX):PREFIX = /usr/local
isEmpty(LIBDIR):LIBDIR = $${PREFIX}/lib
isEmpty(BINDIR):BINDIR = $${PREFIX}/bin
isEmpty(DATADIR):DATADIR = $${PREFIX}/share/walrush
isEmpty(LEVELDIR):LEVELDIR = $${DATADIR}/levels

DEFINES += DATADIR=\"\\\"$${DATADIR}\\\"\" \
           LEVELDIR=\"\\\"$${LEVELDIR}\\\"\"

}

win32: {

}
