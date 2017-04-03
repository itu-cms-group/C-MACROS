# C-MACROS

Delphes_3.4.0 ile nTupler kodunu çalıştırmak için, öncelikli olarak linkler tanımlanmalı. Dephes ile nTupler aynı klasörde bulunmalılar
vi mkLinks
  ln -s ../Delphes-3.4.0/external/ExRootAnalysis .
  ln -s ../Delphes-3.4.0/classes .
  ln -s ../Data .
  cd Batch
  ln -s ../nTupler .
  cd -

mkLinks dosyası bu şekilde kaydedilmeli. Daha önce nTupler klasörü içinde ExRootAnalysis, classes, Data klasörleri mevcutsa silmek
en matıklısı çünkü Delphes_3.4.0 ile haberleştrimek istiyoruz. Ayrıca nTupler kasör içindeki Batch klasörüne bakıldığında bir link
daha görülür. Bunu da silmek gerekebilir.

  rm ExRootAnalysis classes Data
  cd Batch
  rm nTupler
  cd .. 
  mkdir Data 
Bu şekilde bağlantı kurulması istenen Data klasörü de oluşturulmuş olur.
  cp /your/root/file/that/is/converted/hepmc/to/root Data/     (bu kısımdan hala %100 emin değilim ancak bu şekilde çalışıyor)
  cd nTupler
  vi trick.txt
  source trick.txt
  ./mkLinks
  ls -ltrh
ile linkler ekrandan görülebilir.
  ./nTupler nTupler/yapılmak/istenen/root/dosyası  output.root
  
Eğer delphes'in başka versiyonu isteniyorsa en yukardaki linkler ona bağlı olarak değiştirilmeli.
