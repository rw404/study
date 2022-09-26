# Лекция №4 - CNN


```python
import torch
from torch import nn
import torch.nn.functional as F
```

## Полносвязная классификация

- Используем изображение для представления в виде одномерного вектора;
- домножаем на специальный вектор весов;
- прибавляем смещение и полчаем вектор вероятностей классов.


```python
class Mlinear(nn.Module):
    def __init__(self, input_size, ouput_size):
        super(Mlinear, self).__init__()
        self.conv = nn.Conv2d(in_channels=1, out_channels=10, kernel_size=28)
        
    def forward(self, x, verbose=False):
        x = self.conv(x)
        x = x.view(-1, 10)
        x = F.log_softmax(x, dim=1)
        return x
```

__Проблемы сети:__
- простая модель;
- объекты расположены в одном месте кадра;
- много параметров для простой задачи.

### Сверточные нейронные сети(ConvNet, CNN)

- оперируем не пикселями, а объектами(реализация механизма свертки):
    $(I\times K)_{xy}=\sum_{i=1}^h\sum_{j=1}^rK_{ij}I_{x+i-1, y+j-1}$
- свертка извлекает паттерны объекта вместо свзяей пикселей;
- свертку можно понимать, как __фильтр__ - специальная матрица $I$ из п.1, которая применяет задаваемый эффект к изображению(размытие, Собель и тд), __НО__
- в cnn фильтры обучаемые, т.е. специально выделять границы не будут, будут учиться __извлекать искомые паттерны__;
- важное отличие от полносвязных - __чем больше слоев, тем лучше описание объекта__, т.е. больше сверток - лучше, с полносвязными не так.

Характеристики сверток:
- число входных(выходных) каналов;
- шаг свертки;
- отступ;
- размер ядра.

__Когда добавляется свертка, то увеличивается число каналов карты отклика__.

`dilation` - зазор _между пикселями в одном фильтре_


```python
input = torch.randn(20, 16, 50, 100)
m = nn.Conv2d(16, 32, (3, 5), stride=(2, 1), padding=(4, 2), dilation=(3, 1))

m(input).shape
```




    torch.Size([20, 32, 26, 100])



### Линейная операция

- Свертка реализует линейное преобразование, поэтому для работы свертки нужно быстро умножать матрицы(используя параллелизм, ускоряем процесс обучения - __CUDA__)

#### Одноканальная свертка

- помогает менять число каналов, сохраняя пространственную информацию

## Pooling

- Свертки показыают отклик на признаки в каждом сегменте кадра - __нужно находить объект инвариантно от смещений__
- Для этого реализуют __пулинг__ - преобразование, инвариантное к сдвигам в рамках локальной области.

Параметр `ceil_mode` - как вычислять размер результата, когда на заданные кадры изображение не делится.

__Backprop__:
1. Когда вычисляем max-pool, запоминаем позиции максимумов;
2. В ходе обратного распространения заполняем все нулями кроме позиций, где был изначально максимум.


```python
input = torch.randn(20, 16, 50, 32)

m = nn.MaxPool2d((3, 2), stride=(2, 1))

print(m(input).shape)
```

    torch.Size([20, 16, 24, 31])


### Строение сети CNN

__[Conv, NonLinear, Pool] $\times$ k__:
- построили карту отклика для фильтров на всем изображении;
- сохранили релевантные значения из всех откликов;
- использовали пулинг для сокращения размерности и сохранения инвариантности алгоритма.



```python
f = nn.Conv2d(in_channels=1, out_channels=1, kernel_size=3)
x = torch.randn(1, 1, 28, 28)
print(x.shape)
x = f(x)
print(x.shape)
x = F.max_pool2d(x, kernel_size=2)
print(x.shape)
x = f(x)
print(x.shape)
x1 = F.max_pool2d(x, kernel_size=2, ceil_mode=True)
print(x1.shape)
print("ceil_mode=True\nOR")
x2 = F.max_pool2d(x, kernel_size=2)
print(x2.shape)
print("ceil_mode=False")
```

    torch.Size([1, 1, 28, 28])
    torch.Size([1, 1, 26, 26])
    torch.Size([1, 1, 13, 13])
    torch.Size([1, 1, 11, 11])
    torch.Size([1, 1, 6, 6])
    ceil_mode=True
    OR
    torch.Size([1, 1, 5, 5])
    ceil_mode=False


    /usr/local/lib/python3.9/site-packages/torch/nn/functional.py:780: UserWarning: Note that order of the arguments: ceil_mode and return_indices will changeto match the args list in nn.MaxPool2d in a future release.
      warnings.warn("Note that order of the arguments: ceil_mode and return_indices will change"


## Flatten

После применения CNN остается уменьшенная карта признаков, но для работы полносвязного модуля нужно представить эту карту как вектор, для этого:
- можно _вытянуть_ отклики в один вектор;
- GAP - сохранение ключевой информации с каждого слоя.

## Архитектуры CNN


```python
class LeNet5(nn.Module):
    def __init__(sel, n_classes):
        super(LeNet5, self).__init__()
        
        self.feature_extractor = nn.Sequential(
            nn.Conv2d(1, 6, 5, stride=1),
            nn.Tanh(),
            nn.AvgPool2d(kernel_size=2),
            nn.Conv2d(6, 16, 5, stride=1),
            nn.Tanh(),
            nn.AvgPool2d(kernel_size=2),
            nn.Conv2d(16, 120, 5, stride=1),
            nn.Tanh(),
        )
        
        self.classifier = nn.Sequential(
            nn.Linear(120, 84),
            nn.Tanh(),
            nn.Linear(84, n_classes),
        )
    def forward(self, x):
        x = self.feature_extractor(x)
        x = torch.flatten(x)
        logits = self.classifier(x)
        probs = F.softmax(logits, dim=1)
        return logits, probs
```

### AlexNet

- Использует два параллельных пути(использовалось, чтобы задействовать одновременно две GPU)
- Используется ReLU, Dropout, Augmentations

> Ключевая сложность сети все равно хранится в голове, т.к. из __обширного итогового признакового проастранства__ нужно получить __значительно меньшее число значений__

### VGG

- Все свертки __$3\times3$__:
    - двукратное применение простых сверток эквивалентно одинарному применению усложненной;
- Очень много параметров $\sim130M$;
- Более глубокая сеть;
- Обучали более простую сеть, затем полученными весами инициализировали более сложную сеть и дообучали уже ее;
- Сжимает размеры карты, увеличивает количество каналов вдвое.


```python
class VGG(nn.Module):
    def __init__(self, features, num_classes=1000):
        super(VGG, self).__init__()
        
        self.features=features
        self.classifier = nn.Sequential(
            nn.Linear(512*7*7, 4096),
            nn.ReLU(True),
            nn.Dropout(), 
            nn.Linear(4096, 4096),
            nn.ReLU(True),
            nn.Dropout(), 
            nn.Linear(4096, num_classes)
        )
    def forward(self, x):
        x = self.features(x)
        x = x.view(x.size(0), -1)
        logits = self.classifier(x)
        return logits
    
cfg = {
    'A': [64, 'M', 128, 'M', 256, 256, 'M', 512, 512, 'M', 512, 512, 'M'],
    'B': [64, 64, 'M', 128, 128, 'M', 256, 256, 'M', 512, 512, 'M', 512, 512, 'M'],
}

def make_layers(cfg, batch_norm=False):
    layers = []
    in_channels = 3
    for v in cfg:
        if v == 'M':
            layers += [nn.MaxPool2d(kernel_size=2, stride=2)]
        else:
            conv2d = nn.Conv2d(in_channels, v, kernel_size=3, padding=1)
            if batch_norm:
                layers += [conv2d, nn.BatchNorm2d(v), nn.ReLU(inplace=True)]
            else:
                layers += [conv2d, nn.ReLU(inplace=True)]
            in_channels = v
    return nn.Sequential(*layers)

def vgg11(**kwargs):
    model = VGG(make_layers(cfg['A']), **kwargs)
    return model
```


```python
vgg11()
```




    VGG(
      (features): Sequential(
        (0): Conv2d(3, 64, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1))
        (1): ReLU(inplace=True)
        (2): MaxPool2d(kernel_size=2, stride=2, padding=0, dilation=1, ceil_mode=False)
        (3): Conv2d(64, 128, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1))
        (4): ReLU(inplace=True)
        (5): MaxPool2d(kernel_size=2, stride=2, padding=0, dilation=1, ceil_mode=False)
        (6): Conv2d(128, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1))
        (7): ReLU(inplace=True)
        (8): Conv2d(256, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1))
        (9): ReLU(inplace=True)
        (10): MaxPool2d(kernel_size=2, stride=2, padding=0, dilation=1, ceil_mode=False)
        (11): Conv2d(256, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1))
        (12): ReLU(inplace=True)
        (13): Conv2d(512, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1))
        (14): ReLU(inplace=True)
        (15): MaxPool2d(kernel_size=2, stride=2, padding=0, dilation=1, ceil_mode=False)
        (16): Conv2d(512, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1))
        (17): ReLU(inplace=True)
        (18): Conv2d(512, 512, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1))
        (19): ReLU(inplace=True)
        (20): MaxPool2d(kernel_size=2, stride=2, padding=0, dilation=1, ceil_mode=False)
      )
      (classifier): Sequential(
        (0): Linear(in_features=25088, out_features=4096, bias=True)
        (1): ReLU(inplace=True)
        (2): Dropout(p=0.5, inplace=False)
        (3): Linear(in_features=4096, out_features=4096, bias=True)
        (4): ReLU(inplace=True)
        (5): Dropout(p=0.5, inplace=False)
        (6): Linear(in_features=4096, out_features=1000, bias=True)
      )
    )



### GoogleNet

- 3 выхода(тройная ошибка и возможность избежать затухания градиентов);
- используются GAP, поэтому отказ от полносвязных слоев.

#### Inception

- Вход распределяется на 4 параллельных пути:
    - $1\times1$ свертки;
    - $3\times3$ свертки;
    - $5\times5$ свертки;
    - $3\times3$ max-pooling;
    - __Проблема в итоговом числе каналов, поэтому добавляются одноканальные свертки__
- В 3-ей версии Inception идея факторизации сверток(Линал - ранг произведения не превосходит ранга множителей, поэтому ранг свертки должен быть 1, ранг 0 - нулевая матрица):
    - Тогда вместо свертки с матрицей можно две свертки с векторами(упрощение)


```python
class Inception_base(nn.Module):
    def __init__(self, depth_dim, input_size, config):
        super(Inception_base, self).__init__()
        self.depth_dim = depth_dim
        # 1x1
        self.conv1 = nn.Conv2d(input_size, out_channels=config[0][0], kernel_size=1, stride=1, padding=0)
        # 3x3_bottleneck + 3x3
        self.conv3_1 = nn.Conv2d(input_size, out_channels=config[1][0], kernel_size=1, stride=1, padding=0)
        self.conv3_3 = nn.Conv2d(config[1][0], config[1][1], kernel_size=3, stride=1, padding=1)
        # 5x5_bottleneck + 5x5
        self.conv5_1 = nn.Conv2d(input_size, out_channels=config[2][0], kernel_size=1, stride=1, padding=0)
        self.conv5_5 = nn.Conv2d(config[2][0], config[2][1], kernel_size=5, stride=1, padding=2)
        # maxpool + 1x1
        self.max_pool_1 = nn.MaxPool2d(kernel_size=config[3][0], stride=1, padding=1)
        self.conv_max_1 = nn.Conv2d(input_size, out_channels=config[3][1], kernel_size=1, stride=1,
        padding=0)
        
    def forward(self, input):
        output1 = F.relu(self.conv1(input))
        output2 = F.relu(self.conv3_1(input))
        output2 = F.relu(self.conv3_3(output2))
        output3 = F.relu(self.conv5_1(input))
        output3 = F.relu(self.conv5_5(output3))
        output4 = F.relu(self.conv_max_1(self.max_pool_1(input)))
        return torch.cat([output1, output2, output3, output4], dim=self.depth_dim)
```

### ResNet

- Кроме применения сети добавляется еще исходное значение на каждом применении свертки:
    - Научиться переводить преобразование в 0 проще, чем научить тождественному отображению;
    - Сумма в обратном распространении помогает избавиться от затухания градиентов.
- 152 слоя(в разы больше предшественников);
- GAP;
- BatchNorm;
- SGD+Momentum;
- Убрали Dropout.

> Прокидование в слое помогло уменьшить ошибку в более глубоких сетях


```python
class BasicBlock(nn.Module): # building block ResNet 34 - не bottleneck
    expansion = 1
    def __init__(self, inplanes, planes, stride=1, downsample=None):
        super(BasicBlock, self).__init__()
        self.conv1 = conv3x3(inplanes, planes, stride)
        self.bn1 = nn.BatchNorm2d(planes)
        self.relu = nn.ReLU(inplace=True)
        self.conv2 = conv3x3(planes, planes)
        self.bn2 = nn.BatchNorm2d(planes)
        self.downsample = downsample
        self.stride = stride
    def forward(self, x):
        residual = x
        out = self.conv1(x)
        out = self.bn1(out)
        out = self.relu(out)
        out = self.conv2(out)
        out = self.bn2(out)
        if self.downsample is not None:
            residual = self.downsample(x)
        out += residual
        out = self.relu(out)
        return out
```

### SENet

- В результате работы получает еще вектор важности каждого канала, затем его применяет к полученным каналам;
- Помогает уменьшить ошибку.


```python
class SELayer(nn.Module):
    def __init__(self, channel, reduction=16):
        super(SELayer, self).__init__()
        self.avg_pool = nn.AdaptiveAvgPool2d(1)
        self.fc = nn.Sequential(nn.Linear(channel, channel // reduction, bias=False), 
                                nn.ReLU(inplace=True),
                                nn.Linear(channel // reduction, channel, bias=False),
                                nn.Sigmoid()
                               )
    def forward(self, x):
        b, c, _, _ = x.size()
        y = self.avg_pool(x).view(b, c)
        y = self.fc(y).view(b, c, 1, 1)
        return x * y.expand_as(x)
```


```python

```
