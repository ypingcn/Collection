#include "libdes.h"


Libdes::Libdes()
{
}

Libdes * getSharedLibdes()
{
    return new Libdes();
}

string Libdes::bitsetTostring(bitset<64> bit)
{
    string res;
    for (int i = 0; i < 8; ++i) {
      char c = 0x00;
      for (int j = 7; j >= 0; j--) {
        c = c + bit[i * 8 + j];
        if (j != 0)
          c = c * 2; // left shift
      }
      res.push_back(c);
    }
    return res;
}
bitset<64> Libdes::charToBitset(const char s[8])
{
    bitset<64> bits;
    for (int i = 0; i < 8; ++i)
      for (int j = 0; j < 8; ++j)
        bits[i * 8 + j] = ((s[i] >> j) & 1);
    return bits;
}

void Libdes::generateKeys()
{
    bitset<56> realKey;
    bitset<28> left;
    bitset<28> right;
    bitset<48> compressKey;
    // 去掉奇偶标记位，将64位密钥变成56位
    for (int i = 0; i < 56; ++i)
      realKey[55 - i] = key[64 - PC_1[i]];
    // 生成子密钥，保存在 subKeys[16] 中
    for (int round = 0; round < 16; ++round) {
      // 前28位与后28位
      for (int i = 28; i < 56; ++i)
        left[i - 28] = realKey[i];
      for (int i = 0; i < 28; ++i)
        right[i] = realKey[i];
      // 左移
      left = leftShift(left, shiftBits[round]);
      right = leftShift(right, shiftBits[round]);
      // 压缩置换，由56位得到48位子密钥
      for (int i = 28; i < 56; ++i)
        realKey[i] = left[i - 28];
      for (int i = 0; i < 28; ++i)
        realKey[i] = right[i];
      for (int i = 0; i < 48; ++i)
        compressKey[47 - i] = realKey[56 - PC_2[i]];
      subKey[round] = compressKey;
    }
}

bitset<64> Libdes::encrypt(bitset<64> &plain)
{
    bitset<64> cipher;
    bitset<64> currentBits;
    bitset<32> left;
    bitset<32> right;
    bitset<32> newLeft;
    // 第一步：初始置换IP
    for (int i = 0; i < 64; ++i)
      currentBits[63 - i] = plain[64 - IP[i]];
    // 第二步：获取 Li 和 Ri
    for (int i = 32; i < 64; ++i)
      left[i - 32] = currentBits[i];
    for (int i = 0; i < 32; ++i)
      right[i] = currentBits[i];
    // 第三步：共16轮迭代
    for (int round = 0; round < 16; ++round) {
      newLeft = right;
      right = left ^ f(right, subKey[round]);
      left = newLeft;
    }
    // 第四步：合并L16和R16，注意合并为 R16L16
    for (int i = 0; i < 32; ++i)
      cipher[i] = left[i];
    for (int i = 32; i < 64; ++i)
      cipher[i] = right[i - 32];
    // 第五步：结尾置换IP-1
    currentBits = cipher;
    for (int i = 0; i < 64; ++i)
      cipher[63 - i] = currentBits[64 - IP_1[i]];
    // 返回密文
    return cipher;
}

bitset<64> Libdes::decrypt(bitset<64> &cipher)
{
    bitset<64> plain;
    bitset<64> currentBits;
    bitset<32> left;
    bitset<32> right;
    bitset<32> newLeft;
    // 第一步：初始置换IP
    for (int i = 0; i < 64; ++i)
      currentBits[63 - i] = cipher[64 - IP[i]];
    // 第二步：获取 Li 和 Ri
    for (int i = 32; i < 64; ++i)
      left[i - 32] = currentBits[i];
    for (int i = 0; i < 32; ++i)
      right[i] = currentBits[i];
    // 第三步：共16轮迭代（子密钥逆序应用）
    for (int round = 0; round < 16; ++round) {
      newLeft = right;
      right = left ^ f(right, subKey[15 - round]);
      left = newLeft;
    }
    // 第四步：合并L16和R16，注意合并为 R16L16
    for (int i = 0; i < 32; ++i)
      plain[i] = left[i];
    for (int i = 32; i < 64; ++i)
      plain[i] = right[i - 32];
    // 第五步：结尾置换IP-1
    currentBits = plain;
    for (int i = 0; i < 64; ++i)
      plain[63 - i] = currentBits[64 - IP_1[i]];
    // 返回明文
    return plain;
}

bitset<28> Libdes::leftShift(bitset<28> k, int shift)
{
    bitset<28> tmp = k;
    for (int i = 27; i >= 0; --i) {
      if (i - shift < 0)
        k[i] = tmp[i - shift + 28];
      else
        k[i] = tmp[i - shift];
    }
    return k;
}

bitset<32> Libdes::f(bitset<32> R, bitset<48> k)
{
    bitset<48> expandR;
    // 第一步：扩展置换，32 -> 48
    for (int i = 0; i < 48; ++i)
      expandR[47 - i] = R[32 - E[i]];
    // 第二步：异或
    expandR = expandR ^ k;
    // 第三步：查找S_BOX置换表
    bitset<32> output;
    int x = 0;
    for (int i = 0; i < 48; i = i + 6) {
      int row = expandR[47 - i] * 2 + expandR[47 - i - 5];
      int col = expandR[47 - i - 1] * 8 + expandR[47 - i - 2] * 4 +
                expandR[47 - i - 3] * 2 + expandR[47 - i - 4];
      int num = S_BOX[i / 6][row][col];
      bitset<4> binary(num);
      output[31 - x] = binary[3];
      output[31 - x - 1] = binary[2];
      output[31 - x - 2] = binary[1];
      output[31 - x - 3] = binary[0];
      x += 4;
    }
    // 第四步：P-置换，32 -> 32
    bitset<32> tmp = output;
    for (int i = 0; i < 32; ++i)
      output[31 - i] = tmp[32 - P[i]];
    return output;
}

bitset<6> Libdes::intToBitset6(int val)
{
    bitset<6> res;
    if (val >= 64)
      return res;
    int i = 0;
    while (val) {
      if (val & 1)
        res.set(i, 1);
      val /= 2;
      i++;
    }
    return res;
}

bitset<4> Libdes::intToBitset4(int val)
{
    bitset<4> res;
    if (val >= 16)
      return res;
    int i = 0;
    while (val) {
      if (val & 1)
        res.set(i, 1);
      val /= 2;
      i++;
    }
    return res;
}

int Libdes::bitset4Toint(bitset<4> val)
{
    int res = 0, multi = 1;
    for (int i = 0; i < 4; i++) {
      if (val.test(i))
        res += multi;
      multi *= 2;
    }
    return res;
}

void Libdes::generateInput(bitset<6> inDiff)
{
    sBoxInput.clear();
    for (int i = 0; i < 64; i++) {
      InputType val;
      val.before = intToBitset6(i);
      val.after = val.before ^ inDiff;
      sBoxInput.push_back(val);
    }
}

void Libdes::generateOnput(int sBoxId)
{
    sBoxOutput.clear();
    sBoxOutput.resize(16);
    int row = 0, column = 0, multi = 1;
    int num1 = 0, num2 = 0;
    for (InputType val : sBoxInput) {

      row = val.before.test(0) + val.before.test(5) * 2;
      column = 0, multi = 1;
      for (int i = 1; i <= 4; i++) {
        if (val.before.test(i))
          column += multi;
        multi *= 2;
      }
      num1 = S_BOX[sBoxId][row][column];

      row = val.after.test(0) + val.after.test(5) * 2;
      column = 0, multi = 1;
      for (int i = 1; i <= 4; i++) {
        if (val.after.test(i))
          column += multi;
        multi *= 2;
      }
      num2 = S_BOX[sBoxId][row][column];

      int diff = num1 ^ num2;

      sBoxOutput[diff].vec.push_back(val);
      sBoxOutput[diff].outDiff = intToBitset4(diff);
    }
}

void Libdes::getSBoxDifference(int sBoxId,bitset<6> inDiff)
{
    generateInput(inDiff);
    generateOnput(sBoxId);
}

vector<std::pair< vector< bitset<6> > , bitset<4> > > Libdes::getSBoxOutput() {
    vector<std::pair< vector< bitset<6> > , bitset<4> > > res;
    for(OutputType val : sBoxOutput)
    {
        std::pair<vector< bitset<6> > , bitset<4>> tmp;
        vector<bitset<6>> tmpv;
        for(InputType vval : val.vec)
        {
            tmpv.push_back(vval.before);
        }
        tmp.first = tmpv;
        tmp.second = val.outDiff;
        res.push_back(tmp);
    }
    return res;
}
