/* configure the network */
/* neuron groups */
int EC_LI_II_Multipolar_Pyramidal=sim.createGroup("EC_LI_II_Multipolar_Pyramidal", 
							p.EC_LI_II_Multipolar_Pyramidal_Count, EXCITATORY_NEURON, ANY, GPU_CORES);	
int MEC_LII_Stellate=sim.createGroup("MEC_LII_Stellate", 
							p.MEC_LII_Stellate_Count, EXCITATORY_NEURON, ANY, GPU_CORES);
int EC_LII_Axo_Axonic=sim.createGroup("EC_LII_Axo_Axonic", 
							p.EC_LII_Axo_Axonic_Count, INHIBITORY_NEURON, ANY, GPU_CORES);
int MEC_LII_Basket=sim.createGroup("MEC_LII_Basket", 
							p.MEC_LII_Basket_Count, INHIBITORY_NEURON, ANY, GPU_CORES);
int EC_LII_Basket_Multipolar=sim.createGroup("EC_LII_Basket_Multipolar", 
							p.EC_LII_Basket_Multipolar_Count, INHIBITORY_NEURON, ANY, GPU_CORES);
int CA1_Pyramidal=sim.createGroup("CA1_Pyramidal", 
							p.CA1_Pyramidal_Count, EXCITATORY_NEURON, ANY, GPU_CORES);

/* neuron type parameters */
float s_C,s_k,s_vr,s_vt,s_a,s_b,s_vpeak,s_c,s_d;
s_C=118;s_k=0.98;s_vr=-58.53;s_vt=-43.52;s_a=0.004;s_b=11.69;s_vpeak=7.85;s_c=-52.78;s_d=3;
sim.setNeuronParameters(EC_LI_II_Multipolar_Pyramidal, 204.0f, 0.0f, 0.37f, 0.0f, -70.53f, 0.0f, -39.99f, 
								0.0f, 0.001f, 0.0f, 0.01f, 0.0f, 3.96f, 0.0f, -54.95f, 0.0f, 
								7.0f, 0.0f, 1); // C,k,vr,vt,a,b,vpeak,c,d
sim.setNeuronParameters(MEC_LII_Stellate, 118.0f, 0.0f, 0.98f, 0.0f, -58.53f, 0.0f, -43.52f, 
								0.0f, 0.004f, 0.0f, 11.69f, 0.0f, 7.85f, 0.0f, -52.68f, 0.0f, 
								3.0f, 0.0f, 1);
sim.setNeuronParameters(EC_LII_Axo_Axonic, 20.0f, 0.0f,  1.0f, 0.0f, -55.0f, 0.0f, 
								-40.0f, 0.0f, 0.15f, 0.0f, 8.0f, 0.0f, 25.0f, 0.0f, 
								-55.0f, 0.0f, 200.0f, 0.0f, 1); 
sim.setNeuronParameters(MEC_LII_Basket, 20.0f, 0.0f,  1.0f, 0.0f, -55.0f, 0.0f, 
								-40.0f, 0.0f, 0.15f, 0.0f, 8.0f, 0.0f, 25.0f, 0.0f, 
								-55.0f, 0.0f, 200.0f, 0.0f, 1); 
sim.setNeuronParameters(EC_LII_Basket_Multipolar, 20.0f, 0.0f,  1.0f, 0.0f, -55.0f, 0.0f, 
								-40.0f, 0.0f, 0.15f, 0.0f, 8.0f, 0.0f, 25.0f, 0.0f, 
								-55.0f, 0.0f, 200.0f, 0.0f, 1); 
sim.setNeuronParameters(CA1_Pyramidal, 334.0f, 0.0f, 1.56f, 0.0f, -69.36f, 0.0f, -53.22f, 
								0.0f, 0.0f, 0.0f, -17.25f, 0.0f, 25.46f, 0.0f, -60.22f, 
								0.0f, 16.0f, 0.0f, 1);

/* neuron connection parameters */
setInExcConns(&sim, &p);
MexHatConnection* MexHatConn = new MexHatConnection(&p);
SomeToSomeConnection* SomeToSomeConn = new SomeToSomeConnection(&p);	
static const float g_val = 4.92;
sim.connect(EC_LI_II_Multipolar_Pyramidal, MEC_LII_Stellate, "one-to-one", p.dir_to_gc_wt, 1.0f, 
			RangeDelay(1), RadiusRF(-1), SYN_PLASTIC, 33.082, 0.0f); // 0 DIR
p.conn_offset = 0;
sim.connect(MEC_LII_Stellate, EC_LII_Axo_Axonic, SomeToSomeConn, SYN_FIXED, 9.654, 0.0f);
sim.connect(EC_LII_Axo_Axonic, MEC_LII_Stellate, MexHatConn, SYN_FIXED, 9.654, 0.0f); // 2 IN->GC one-to-many
p.conn_offset = 1;
MexHatConn = new MexHatConnection(&p);
SomeToSomeConn = new SomeToSomeConnection(&p);
sim.connect(MEC_LII_Stellate, MEC_LII_Basket, SomeToSomeConn, SYN_FIXED, 9.654, 0.0f);
sim.connect(MEC_LII_Basket, MEC_LII_Stellate, MexHatConn, SYN_FIXED, 9.654, 0.0f); // 2 IN->GC one-to-many
p.conn_offset = 2;
MexHatConn = new MexHatConnection(&p);
SomeToSomeConn = new SomeToSomeConnection(&p);
sim.connect(MEC_LII_Stellate, EC_LII_Basket_Multipolar, SomeToSomeConn, SYN_FIXED, 9.654, 0.0f);
sim.connect(EC_LII_Basket_Multipolar, MEC_LII_Stellate, MexHatConn, SYN_FIXED, 9.654, 0.0f); // 2 IN->GC one-to-many
sim.connect(CA1_Pyramidal, MEC_LII_Stellate, "one-to-one", 1.0f, 1.0f, 
			RangeDelay(1), RadiusRF(-1), SYN_PLASTIC, g_val, 0.0f); // 3 PCs

/* STP parameters */
/*static const float m1 = 0.1231;//0.0001; // 0-1 range
static const float m2 = 49.71;//1000;
static const float m3 = 153.4;//1000;//0.0001;
static const float m4 = 6.674;//0.0001; 
static const float m5 = 150.0;//1000;
static const float m6 = 6.0;//1000;//0.0001;
static const float m7 = 150.0;//0.0001; */
sim.setSTP(EC_LI_II_Multipolar_Pyramidal, MEC_LII_Stellate, true, STPu(0.1513, 0.0f),
                                     STPtauU(69.11, 0.0f),
                                     STPtauX(98.1, 0.0f),
                                     STPtdAMPA(6.636, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate, EC_LII_Axo_Axonic, true, STPu(0.1514, 0.0f),
                                     STPtauU(58.97, 0.0f),
                                     STPtauX(123.7, 0.0f),
                                     STPtdAMPA(6.632, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate, MEC_LII_Basket, true, STPu(0.1638, 0.0f),
                                     STPtauU(57.57, 0.0f),
                                     STPtauX(119, 0.0f),
                                     STPtdAMPA(6.205, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate, EC_LII_Basket_Multipolar, true, STPu(0.1638, 0.0f),
                                     STPtauU(57.57, 0.0f),
                                     STPtauX(119, 0.0f),
                                     STPtdAMPA(6.205, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(EC_LII_Axo_Axonic, MEC_LII_Stellate, true, STPu(0.1100, 0.0f),
                                     STPtauU(35.53, 0.0f),
                                     STPtauX(355.8, 0.0f),
                                     STPtdAMPA(5.0f, 0.0f),
                                     STPtdNMDA(150.0f, 0.0f),
                                     STPtdGABAa(8.839f, 0.0f),
                                     STPtdGABAb(150.0f, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Basket, MEC_LII_Stellate, true, STPu(0.1119, 0.0f),
                                     STPtauU(37.29, 0.0f),
                                     STPtauX(346.3, 0.0f),
                                     STPtdAMPA(5.0f, 0.0f),
                                     STPtdNMDA(150.0f, 0.0f),
                                     STPtdGABAa(9.137f, 0.0f),
                                     STPtdGABAb(150.0f, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(EC_LII_Basket_Multipolar, MEC_LII_Stellate, true, STPu(0.1119, 0.0f),
                                     STPtauU(41.94, 0.0f),
                                     STPtauX(311.8, 0.0f),
                                     STPtdAMPA(5.0f, 0.0f),
                                     STPtdNMDA(150.0f, 0.0f),
                                     STPtdGABAa(10.022f, 0.0f),
                                     STPtdGABAb(150.0f, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(CA1_Pyramidal, MEC_LII_Stellate, true, STPu(0.1231, 0.0f),
                                     STPtauU(49.71, 0.0f),
                                     STPtauX(153.4, 0.0f),
                                     STPtdAMPA(6.674, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));

/* neuron monitors */
//NeuronMonitor* nrn_mon;
//NeuronMonitor* nrn_mon = sim.setNeuronMonitor(gexc,"DEFAULT");
//nrn_mon->setPersistentData(true);
//NeuronMonitor* nrn_mon2;
//NeuronMonitor* nrn_mon2 = sim.setNeuronMonitor(ginh,"DEFAULT");
//nrn_mon2->setPersistentData(true);
//NeuronMonitor* nrn_mon3;
//NeuronMonitor* nrn_mon3 = sim.setNeuronMonitor(gpcs,"DEFAULT");
//nrn_mon3->setPersistentData(true);

//sim.setNeuronMonitor(MEC_LII_Stellate, "DEFAULT");