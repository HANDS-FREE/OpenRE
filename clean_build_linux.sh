#!/bin/bash
find ./ -name "*.pro.user" | xargs rm -f
find ./ -name "*.bak" | xargs rm -f
find ./ -name "*.ddk" | xargs rm -f
find ./ -name "*.lst" | xargs rm -f
find ./ -name "*.lnp" | xargs rm -f
find ./ -name "*.mpf" | xargs rm -f
find ./ -name "*.mpj" | xargs rm -f
find ./ -name "*.obj" | xargs rm -f
find ./ -name "*.omf" | xargs rm -f
find ./ -name "*.plg" | xargs rm -f
find ./ -name "*.rpt" | xargs rm -f
find ./ -name "*.tmp" | xargs rm -f
find ./ -name "*.__i" | xargs rm -f
find ./ -name "*.crf" | xargs rm -f
find ./ -name "*.o"   | xargs rm -f
find ./ -name "*.d"   | xargs rm -f
find ./ -name "*.axf" | xargs rm -f
find ./ -name "*.tra" | xargs rm -f
find ./ -name "*.dep" | xargs rm -f           
find ./ -name "JLinkLog.txt"     | xargs rm -f
find ./ -name "*.uvguix.mawenke" | xargs rm -f
find ./ -name "*.iex" | xargs rm -f
find ./ -name "*.htm" | xargs rm -f
find ./ -name "*.sct" | xargs rm -f
find ./ -name "*~" | xargs rm -f

