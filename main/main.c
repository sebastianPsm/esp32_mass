#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <esp_log.h>
#include <esp_timer.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <MASS.h>

#define TAG "mass"

unsigned n = 1024;
static float ts[] = { -0.5488, -0.5476, -0.5472, -0.5452, -0.5436, -0.5408, -0.5404, -0.5384, -0.5372, -0.5356, -0.5328, -0.5296, -0.5276, -0.5252, -0.5244, -0.5216, -0.5192, -0.5164, -0.5128, -0.5092, -0.5056, -0.5028, -0.5020, -0.5008, -0.4988, -0.4984, -0.4984, -0.4976, -0.4996, -0.5008, -0.5016, -0.5028, -0.5032, -0.5036, -0.5032, -0.5028, -0.5012, -0.4976, -0.4984, -0.5008, -0.5080, -0.5184, -0.5224, -0.5212, -0.5220, -0.5236, -0.5288, -0.5328, -0.5340, -0.5376, -0.5384, -0.5396, -0.5444, -0.5452, -0.5480, -0.5484, -0.5484, -0.5488, -0.5520, -0.5532, -0.5540, -0.5580, -0.5644, -0.5684, -0.5696, -0.5660, -0.5596, -0.5600, -0.5632, -0.5660, -0.5676, -0.5668, -0.5648, -0.5664, -0.5672, -0.5696, -0.5708, -0.5692, -0.5684, -0.5672, -0.5684, -0.5684, -0.5692, -0.5672, -0.5676, -0.5692, -0.5692, -0.5688, -0.5664, -0.5652, -0.5652, -0.5652, -0.5636, -0.5660, -0.5656, -0.5664, -0.5656, -0.5648, -0.5640, -0.5632, -0.5616, -0.5612, -0.5596, -0.5596, -0.5592, -0.5592, -0.5592, -0.5596, -0.5604, -0.5608, -0.5620, -0.5632, -0.5628, -0.5640, -0.5652, -0.5672, -0.5668, -0.5684, -0.5684, -0.5692, -0.5712, -0.5740, -0.5752, -0.5780, -0.5796, -0.5820, -0.5836, -0.5848, -0.5856, -0.5872, -0.5884, -0.5912, -0.5924, -0.5956, -0.5992, -0.5992, -0.6028, -0.6076, -0.6124, -0.6156, -0.6152, -0.6288, -0.6348, -0.6396, -0.6516, -0.6568, -0.6612, -0.6640, -0.6660, -0.6760, -0.6740, -0.6736, -0.6756, -0.6816, -0.6816, -0.6796, -0.6804, -0.6768, -0.6744, -0.6720, -0.6712, -0.6664, -0.6608, -0.6536, -0.6472, -0.6436, -0.6276, -0.6188, -0.6096, -0.5952, -0.5864, -0.5780, -0.5708, -0.5636, -0.5504, -0.5488, -0.5448, -0.5416, -0.5332, -0.5304, -0.5304, -0.5256, -0.5256, -0.5184, -0.5120, -0.5068, -0.5012, -0.4972, -0.4944, -0.4908, -0.4868, -0.4812, -0.4756, -0.4720, -0.4676, -0.4632, -0.4580, -0.4564, -0.4548, -0.4520, -0.4548, -0.4564, -0.4564, -0.4572, -0.4584, -0.4576, -0.4576, -0.4600, -0.4656, -0.4676, -0.4712, -0.4768, -0.4824, -0.4800, -0.4868, -0.4972, -0.5060, -0.5112, -0.5144, -0.5148, -0.5088, -0.5144, -0.5204, -0.5304, -0.5348, -0.5316, -0.5336, -0.5368, -0.5360, -0.5336, -0.5320, -0.5320, -0.5308, -0.5300, -0.5320, -0.5320, -0.5312, -0.5296, -0.5352, -0.5340, -0.5304, -0.5296, -0.5308, -0.5308, -0.5380, -0.5464, -0.5468, -0.5444, -0.5356, -0.5336, -0.5372, -0.5364, -0.5336, -0.5348, -0.5368, -0.5380, -0.5376, -0.5388, -0.5396, -0.5400, -0.5404, -0.5392, -0.5388, -0.5384, -0.5392, -0.5376, -0.5360, -0.5348, -0.5372, -0.5352, -0.5376, -0.5360, -0.5348, -0.5360, -0.5372, -0.5344, -0.5332, -0.5328, -0.5324, -0.5312, -0.5324, -0.5340, -0.5320, -0.5304, -0.5320, -0.5328, -0.5356, -0.5384, -0.5404, -0.5416, -0.5428, -0.5448, -0.5480, -0.5496, -0.5508, -0.5524, -0.5556, -0.5588, -0.5616, -0.5648, -0.5692, -0.5720, -0.5740, -0.5764, -0.5792, -0.5804, -0.5820, -0.5860, -0.5896, -0.5912, -0.5956, -0.5988, -0.6016, -0.6052, -0.6092, -0.6140, -0.6204, -0.6216, -0.6332, -0.6400, -0.6468, -0.6492, -0.6516, -0.6552, -0.6572, -0.6560, -0.6560, -0.6600, -0.6608, -0.6580, -0.6548, -0.6476, -0.6404, -0.6332, -0.6280, -0.6240, -0.6184, -0.6152, -0.6104, -0.6020, -0.5960, -0.5864, -0.5804, -0.5644, -0.5544, -0.5432, -0.5372, -0.5324, -0.5260, -0.5184, -0.5148, -0.5108, -0.5032, -0.4976, -0.4956, -0.4944, -0.4936, -0.4928, -0.4924, -0.4876, -0.4796, -0.4736, -0.4652, -0.4580, -0.4544, -0.4488, -0.4456, -0.4408, -0.4380, -0.4332, -0.4348, -0.4336, -0.4324, -0.4336, -0.4388, -0.4432, -0.4472, -0.4516, -0.4568, -0.4604, -0.4636, -0.4740, -0.4832, -0.4960, -0.5064, -0.5104, -0.5172, -0.5228, -0.5292, -0.5404, -0.5444, -0.5504, -0.5552, -0.5608, -0.5668, -0.5664, -0.5700, -0.5724, -0.5720, -0.5704, -0.5680, -0.5664, -0.5652, -0.5620, -0.5612, -0.5612, -0.5572, -0.5540, -0.5476, -0.5436, -0.5476, -0.5484, -0.5508, -0.5520, -0.5476, -0.5496, -0.5492, -0.5524, -0.5532, -0.5544, -0.5560, -0.5552, -0.5544, -0.5556, -0.5548, -0.5544, -0.5536, -0.5524, -0.5532, -0.5528, -0.5524, -0.5516, -0.5496, -0.5464, -0.5460, -0.5444, -0.5428, -0.5420, -0.5412, -0.5396, -0.5396, -0.5388, -0.5392, -0.5400, -0.5404, -0.5412, -0.5412, -0.5420, -0.5408, -0.5416, -0.5420, -0.5432, -0.5444, -0.5452, -0.5472, -0.5488, -0.5508, -0.5532, -0.5572, -0.5588, -0.5612, -0.5640, -0.5648, -0.5676, -0.5716, -0.5748, -0.5780, -0.5792, -0.5820, -0.5840, -0.5872, -0.5900, -0.5928, -0.5972, -0.6000, -0.6036, -0.6064, -0.6092, -0.6124, -0.6160, -0.6216, -0.6280, -0.6352, -0.6424, -0.6508, -0.6592, -0.6612, -0.6688, -0.6772, -0.6816, -0.6912, -0.7020, -0.7100, -0.7208, -0.7296, -0.7396, -0.7416, -0.7416, -0.7364, -0.7296, -0.7224, -0.7172, -0.7128, -0.7084, -0.7068, -0.7036, -0.6988, -0.6924, -0.6844, -0.6792, -0.6700, -0.6668, -0.6556, -0.6444, -0.6332, -0.6180, -0.6024, -0.5912, -0.5732, -0.5568, -0.5396, -0.5280, -0.5188, -0.5124, -0.5080, -0.5024, -0.4972, -0.4884, -0.4796, -0.4656, -0.4548, -0.4424, -0.4328, -0.4260, -0.4212, -0.4216, -0.4196, -0.4200, -0.4184, -0.4180, -0.4188, -0.4212, -0.4252, -0.4240, -0.4280, -0.4292, -0.4300, -0.4396, -0.4436, -0.4508, -0.4548, -0.4588, -0.4716, -0.4820, -0.4892, -0.4924, -0.5020, -0.5104, -0.5180, -0.5200, -0.5196, -0.5184, -0.5184, -0.5188, -0.5228, -0.5240, -0.5224, -0.5192, -0.5232, -0.5228, -0.5232, -0.5296, -0.5328, -0.5352, -0.5356, -0.5400, -0.5428, -0.5412, -0.5424, -0.5468, -0.5516, -0.5508, -0.5500, -0.5476, -0.5472, -0.5468, -0.5496, -0.5520, -0.5532, -0.5528, -0.5528, -0.5540, -0.5540, -0.5536, -0.5536, -0.5544, -0.5544, -0.5476, -0.5492, -0.5492, -0.5492, -0.5488, -0.5468, -0.5440, -0.5428, -0.5412, -0.5412, -0.5408, -0.5420, -0.5408, -0.5404, -0.5404, -0.5404, -0.5400, -0.5408, -0.5424, -0.5436, -0.5456, -0.5476, -0.5492, -0.5520, -0.5532, -0.5540, -0.5548, -0.5556, -0.5572, -0.5588, -0.5612, -0.5628, -0.5640, -0.5680, -0.5708, -0.5732, -0.5740, -0.5756, -0.5776, -0.5804, -0.5836, -0.5900, -0.5956, -0.6004, -0.6056, -0.6108, -0.6168, -0.6244, -0.6268, -0.6328, -0.6356, -0.6388, -0.6440, -0.6532, -0.6592, -0.6636, -0.6708, -0.6800, -0.6844, -0.6864, -0.6904, -0.6896, -0.6868, -0.6824, -0.6788, -0.6736, -0.6676, -0.6608, -0.6528, -0.6444, -0.6352, -0.6276, -0.6192, -0.6136, -0.6052, -0.5976, -0.5916, -0.5840, -0.5712, -0.5620, -0.5516, -0.5388, -0.5220, -0.5076, -0.4980, -0.4868, -0.4780, -0.4724, -0.4684, -0.4640, -0.4608, -0.4544, -0.4464, -0.4412, -0.4348, -0.4308, -0.4228, -0.4160, -0.4136, -0.4116, -0.4104, -0.4076, -0.4100, -0.4148, -0.4204, -0.4272, -0.4244, -0.4260, -0.4368, -0.4464, -0.4544, -0.4564, -0.4632, -0.4668, -0.4700, -0.4744, -0.4860, -0.4980, -0.5052, -0.5128, -0.5184, -0.5256, -0.5380, -0.5432, -0.5468, -0.5508, -0.5544, -0.5536, -0.5508, -0.5464, -0.5440, -0.5524, -0.5588, -0.5556, -0.5524, -0.5504, -0.5564, -0.5580, -0.5624, -0.5656, -0.5668, -0.5636, -0.5620, -0.5636, -0.5652, -0.5672, -0.5692, -0.5640, -0.5628, -0.5616, -0.5632, -0.5640, -0.5644, -0.5640, -0.5644, -0.5628, -0.5608, -0.5584, -0.5568, -0.5544, -0.5516, -0.5504, -0.5480, -0.5452, -0.5424, -0.5400, -0.5360, -0.5336, -0.5312, -0.5296, -0.5276, -0.5256, -0.5240, -0.5236, -0.5240, -0.5236, -0.5248, -0.5252, -0.5264, -0.5276, -0.5304, -0.5308, -0.5328, -0.5352, -0.5372, -0.5404, -0.5420, -0.5440, -0.5468, -0.5496, -0.5524, -0.5552, -0.5556, -0.5568, -0.5580, -0.5596, -0.5620, -0.5648, -0.5672, -0.5688, -0.5704, -0.5740, -0.5760, -0.5792, -0.5844, -0.5888, -0.5948, -0.6000, -0.6044, -0.6112, -0.6148, -0.6180, -0.6256, -0.6256, -0.6284, -0.6392, -0.6476, -0.6528, -0.6568, -0.6548, -0.6556, -0.6548, -0.6476, -0.6412, -0.6388, -0.6352, -0.6276, -0.6240, -0.6204, -0.6140, -0.6072, -0.5992, -0.5908, -0.5832, -0.5728, -0.5640, -0.5572, -0.5444, -0.5392, -0.5304, -0.5156, -0.5036, -0.4948, -0.4868, -0.4832, -0.4756, -0.4688, -0.4696, -0.4684, -0.4632, -0.4592, -0.4556, -0.4488, -0.4404, -0.4344, -0.4264, -0.4220, -0.4180, -0.4144, -0.4144, -0.4128, -0.4144, -0.4176, -0.4188, -0.4212, -0.4248, -0.4248, -0.4340, -0.4344, -0.4340, -0.4360, -0.4384, -0.4448, -0.4496, -0.4552, -0.4664, -0.4760, -0.4892, -0.4980, -0.5080, -0.5160, -0.5172, -0.5208, -0.5272, -0.5308, -0.5340, -0.5344, -0.5352, -0.5392, -0.5432, -0.5432, -0.5456, -0.5412, -0.5460, -0.5532, -0.5596, -0.5648, -0.5652, -0.5668, -0.5684, -0.5644, -0.5632, -0.5596, -0.5608, -0.5588, -0.5604, -0.5668, -0.5700, -0.5696, -0.5688, -0.5716, -0.5724, -0.5728, -0.5712, -0.5688, -0.5684, -0.5696, -0.5696, -0.5688, -0.5684, -0.5672, -0.5668, -0.5648, -0.5636, -0.5624, -0.5628, -0.5620, -0.5608, -0.5596, -0.5576, -0.5572, -0.5572, -0.5572, -0.5572, -0.5580, -0.5576, -0.5584, -0.5604, -0.5612, -0.5620, -0.5632, -0.5628, -0.5628, -0.5628, -0.5628, -0.5632, -0.5632, -0.5660, -0.5692, -0.5720, -0.5724, -0.5736, -0.5756, -0.5768, -0.5792, -0.5800, -0.5804, -0.5824, -0.5852, -0.5884, -0.5924, -0.5964, -0.5996, -0.6052, -0.6144, -0.6176, -0.6240, -0.6240, -0.6252, -0.6288, -0.6364, -0.6448, -0.6512, -0.6536, -0.6564, -0.6588, -0.6592, -0.6556, -0.6536, -0.6480, -0.6420, -0.6364, -0.6300, -0.6232, -0.6212, -0.6152, -0.6116, -0.6044, -0.5952, -0.5852, -0.5796, -0.5704, -0.5684, -0.5628, -0.5560, -0.5456, -0.5344, -0.5232, -0.5116, -0.4996, -0.4892, -0.4800, -0.4740, -0.4696, -0.4684, -0.4668, -0.4656, -0.4644, -0.4592, -0.4488, -0.4444, -0.4380, -0.4336, -0.4304, -0.4256, -0.4240, -0.4260, -0.4228, -0.4256, -0.4276, -0.4236, -0.4268, -0.4384, -0.4472, -0.4616, -0.4804, -0.4984 };
unsigned m = 128;
static float q[] = { -0.4804, -0.4736, -0.4628, -0.4488, -0.4336, -0.4172, -0.4020, -0.3880, -0.3732, -0.3508, -0.3300, -0.3096, -0.2904, -0.2728, -0.2532, -0.2348, -0.2156, -0.2008, -0.1864, -0.1744, -0.1624, -0.1504, -0.1440, -0.1356, -0.1268, -0.1200, -0.1164, -0.1168, -0.1184, -0.1200, -0.1316, -0.1356, -0.1372, -0.1416, -0.1488, -0.1632, -0.1724, -0.1784, -0.1792, -0.1840, -0.1976, -0.2084, -0.2164, -0.2320, -0.2496, -0.2660, -0.2828, -0.2936, -0.3004, -0.3104, -0.3200, -0.3280, -0.3300, -0.3308, -0.3332, -0.3340, -0.3388, -0.3448, -0.3476, -0.3488, -0.3416, -0.3400, -0.3400, -0.3472, -0.3516, -0.3496, -0.3504, -0.3580, -0.3580, -0.3568, -0.3564, -0.3560, -0.3588, -0.3652, -0.3672, -0.3648, -0.3600, -0.3624, -0.3632, -0.3624, -0.3556, -0.3524, -0.3508, -0.3476, -0.3460, -0.3444, -0.3412, -0.3372, -0.3348, -0.3344, -0.3328, -0.3324, -0.3316, -0.3324, -0.3332, -0.3324, -0.3312, -0.3308, -0.3324, -0.3352, -0.3392, -0.3436, -0.3440, -0.3452, -0.3464, -0.3476, -0.3492, -0.3512, -0.3544, -0.3576, -0.3608, -0.3652, -0.3724, -0.3768, -0.3792, -0.3816, -0.3840, -0.3840, -0.3856, -0.3880, -0.3924, -0.3972, -0.4004, -0.4028, -0.4068, -0.4140, -0.4212, -0.4300 };

void find_motifs(void * data) {
    tMass * mass;
    float * dist = (float *) calloc(n-m+1, sizeof(float));
     
    mass = mass_init(n, m);
    mass_findNN(mass, ts, q, dist);
    mass_terminate(&mass);
    
    // print distances
    printf("dist: ");
    for (unsigned idx = 0; idx < n - m + 1; idx++)
      printf("%f, ", dist[idx]);
    printf("\n");
    
    free(dist);

    // Benchmark
    printf("Benchmark: \n");
    printf("n, m, t[us]\n");
    unsigned int ns[] = {256, 512, 1024};
    unsigned int ms[] = {4, 8, 16, 32, 64, 128};
    for(unsigned idx = 0; idx < 3; idx++) {
      for(unsigned jdx = 0; jdx < 6; jdx++) {
        mass = mass_init(ns[idx], ms[jdx]);

        int64_t start = esp_timer_get_time();
        mass_findNN(mass, ts, q, dist);
        int64_t end = esp_timer_get_time();

        printf("%u, %u, %lld\n", ns[idx], ms[jdx], (long long) end-start);

        mass_terminate(&mass);
      }
    }
    

    while(1);
}

void app_main(void) {
    xTaskCreate(find_motifs, "find_motifs", 16*1014, NULL, 6, NULL);
}
