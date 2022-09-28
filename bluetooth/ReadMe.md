# 说明

CompanyIdentfiers - CSV.csv为厂商ID数据,下载地址:https://www.bluetooth.com/specifications/assigned-numbers/company-identifiers/

生成

```bash
awk 'BEGIN{print "#include \"ble_company_id.h\"\n";print "const ble_company_id_t ble_company_id[]=\n{";}{ if(NR > 1) {print "{";print $0;print "},"}}END{print "{0}\n};\n"}' "CompanyIdentfiers - CSV.csv" > ble_company_id_data.c
```

