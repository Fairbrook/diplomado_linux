#! /bin/bash

rm test_KAMV.txt
echo "Goodbye" > test.txt

echo "diff --git a/test.txt b/test_KAMV.txt
rename from test.txt
rename to test_KAMV.txt
--- a/test.txt
+++ b/test_KAMV.txt
@@ -1 +1,2 @@
-Goodbye
+Hello
+World" > test.patch

git apply test.patch
