from PIL import Image
import numpy as np

def resize(pic_name,size = (960,640),save_name = 'test.png'):
    img = Image.open(pic_name)
    img = img.resize(size)
    img.save(save_name)

def cut(pic_name,x,y,width = 960,height = 640,save_name = 'test.png'):
    """
    x:横坐标
    y:纵坐标
    width:宽度
    heighte:高度
    save_name:处理后的图片保存的文件名
    """
    img = Image.open(pic_name)
    img = img.crop((x,y,x+width,y+height))
    # img.show()
    img.save(save_name)

def transposeMirror(pic_name,save_name = 'test.jpg'):
    img = Image.open(pic_name)
    out = img.transpose(Image.FLIP_LEFT_RIGHT) 
    out.save(save_name)

def transpose(pic_name,save_name = 'test.jpg',trans = Image.ROTATE_90):
    img = Image.open(pic_name)
    out = img.transpose(trans) 
    out.save(save_name)

def toBlack(pic_name):
    img = Image.open(pic_name)
    width,height = img.size
    img = img.convert("L") 
    for h in range(height):
        for w in range(width):
            if img.getpixel((w,h)) < 100:
                img.putpixel((w,h),1)
            elif img.getpixel((w,h)) > 200:
                img.putpixel((w,h),255)
    # img.show()
    img.save(pic_name)

if __name__ == '__main__':
    # cut('2.jpg',330,300,140,100,'test.jpg')
    # transpose('test.jpg')
    # resize('hp_adder.jpg',(50,50),'hp_adder.jpg')
    # resize('1604.png')
    toBlack('Thing\\bag.jpg')