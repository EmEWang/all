

osgearth中labelcontrol设置中文
1.将字符串转换为中文（gb2312->unicode->Utf8）
    //记得加上头文件
    #include <Windows.h>

    //转换为中文字符进行显示
    void gb2312ToUnicode(const string& src, wstring& result)
    {
        int n = MultiByteToWideChar(CP_ACP, 0, src.c_str(), -1, NULL, 0);
        result.resize(n);
        ::MultiByteToWideChar(CP_ACP, 0, src.c_str(), -1, (LPWSTR)result.c_str(), result.length());
    }

    void unicodeToUTF8(const wstring &src, string& result)
    {
        int n = WideCharToMultiByte(CP_UTF8, 0, src.c_str(), -1, 0, 0, 0, 0);
        result.resize(n);
        ::WideCharToMultiByte(CP_UTF8, 0, src.c_str(), -1, (char*)result.c_str(), result.length(), 0, 0);
    }

    void gb2312ToUtf8(const string& src, string& result)
    {
        wstring strWideChar;
        gb2312ToUnicode(src, strWideChar);
        unicodeToUTF8(strWideChar, result);
    }

2. 设置字体和本地编码
    osgEarth::Util::Controls::LabelControl *cameraShow = new osgEarth::Util::Controls::LabelControl("hh", Color::White);
    cameraShow->setBackColor(osgEarth::Util::Controls::Color(osgEarth::Util::Controls::Color::Green, 0.5));
    const string allStr = str0 + str1 + str2 + str3 + str4 + str5 + str6 + str7 + str8 + str9;//这里设置你自己想要的字符串
    string allStrUtf8;
    gb2312ToUtf8(allStr, allStrUtf8);//字体转换

    //设置字体和本地编码
    osgText::Font* fonts = osgText::readFontFile("666.ttf");//这里设置你自己想要的字体
    cameraShow->setEncoding(osgText::String::ENCODING_UTF8);//设置本地编码
    cameraShow->setText(allStrUtf8);
    cameraShow->setFont(fonts);




osg Image 保存图片
osg::ref_ptr<osg::Texture2D> texture2d = new osg::Texture2D;
osg::ref_ptr<osg::Image> img = new osg::Image;
img=osgDB::readImageFile("C:\\Users\\Public\\Pictures\\Sample Pictures\\Tulips.jpg");
osg::ref_ptr<osg::Image> img2 = new osg::Image;
img2->setImage(img->s(),img->t(),img->r(),img->getInternalTextureFormat(),img->getPixelFormat(),img->getDataType(),img->data(),img->getAllocationMode());
osgDB::writeImageFile(*img2,"img2.jpg");
osgDB::writeImageFile(*img,"abc.jpg");
texture2d->setImage(img);







