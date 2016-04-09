#include "SimpleStatisticsProject.h"

void SimpleStatisticsProject::Dataset(int N,int n,string str){
    m_n=n;
    m_data.clear();
    m_data.resize(m_n);
    m_str=str;
    m_N=N;
    int i=0,j=0;
    double tmp;

    //Random number generator engine
    std::random_device rd;
    std::mt19937_64 rseed(rd());
    //Random distribution`
    std::uniform_real_distribution<double> dr(0,1);//From 0 to 1

    //store the dataset to file
    m_out.open(m_str+"_dataset.txt",ios::app);
    m_out<<"#Dataset\n";
    m_out<<"#N:"<<m_N<<",n:"<<m_n<<"\n";

    for(i=0;i<m_n;i++){
        tmp=0;
        for(j=0;j<m_N;j++){
            tmp+=dr(rseed);

        }
        tmp/=m_N;
        m_data[i]=tmp;
        m_out<<tmp<<"\n";
    }
    m_out<<"\n\n";
    m_out.close();
    m_out.clear();
    //cout<<"Successful construct data set!\n";
}

void SimpleStatisticsProject::Histogram(int s){
    m_s = s;
    m_n=m_data.size();
    vector<int> freq(s);

    //set all elements to 0
    for(vector<int>::iterator iter=freq.begin();iter!=freq.end();iter++) *iter=0;
    for(int i=0;i<m_n;i++)
        freq[int(m_data[i]*s)]++;

    m_out.open(m_str+"_freqtable.txt",ios::app);
    m_out<<"#Dataset\n";
    m_out<<"#N:"<<m_N<<",n:"<<m_n<<",s:"<<s<<"\n";
    for(int i=0;i<s;i++){
        m_out<<i*1.0/s+1.0/s/2<<"\t"<<1.0*freq[i]/m_n<<"\n";
    }
    m_out<<"\n\n";
    m_out.close();
    m_out.clear();
}

void SimpleStatisticsProject::Statistic(){
    m_n=m_data.size();
    avera=0,avestandevia=0;
    for(int i=0;i<m_n;i++){
        avera+=m_data[i];
        avestandevia+=m_data[i]*m_data[i];
    }
    avera/=m_n;//average
    avestandevia = sqrt( (avestandevia/m_n-avera*avera) / (m_n-1) );//standard deviation of average

    m_out.open(m_str+"_stat.txt",ios::app);
    m_out<<"#Dataset\n";
    m_out<<"#N:"<<m_N<<",n:"<<m_n<<",s:"<<m_s<<"\n";

    m_out<<"average\t"<<avera<<endl;
    m_out<<"average standard deviation\t"<<avestandevia<<endl;
    m_out<<"\n\n";
    m_out.close();
    m_out.clear();
}

void SimpleStatisticsProject::PautaFilter(){
    std::vector<double> store;
    for(int i=0;i<m_n;i++){
        if(m_data[i]<avera-3*avestandevia*sqrt(m_n) || m_data[i]>avera+3*avestandevia*sqrt(m_n)) continue;//Use Pauta method to filter wrong points
        store.push_back(m_data[i]);
    }
    m_n = store.size();
    m_data.clear();
    m_data = store;
    m_str=m_str+"_filter";
    //print infomation
    m_out.open(m_str+"_dataset.txt",ios::app);
    m_out<<"#Dataset\n";
    m_out<<"#N:"<<m_N<<",n:"<<m_n<<"\n";

    for(int i=0;i<m_n;i++){
        m_out<<m_data[i]<<endl;
    }
    m_out<<"\n\n";
    m_out.close();
    m_out.clear();

}
