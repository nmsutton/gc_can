/* configure the network */
/* neuron groups */
int MEC_LII_Stellate_ExtDir=sim.createGroup("MEC_LII_Stellate_ExtDir", 
							p.MEC_LII_Stellate_ExtDir_Count, EXCITATORY_NEURON, ANY, GPU_CORES);	
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
sim.setNeuronParameters(MEC_LII_Stellate_ExtDir, s_C, 0.0f, s_k, 0.0f, s_vr, 0.0f, s_vt, 
								0.0f, s_a, 0.0f, s_b, 0.0f, s_vpeak, 0.0f, s_c, 0.0f, 
								s_d, 0.0f, 1); // C,k,vr,vt,a,b,vpeak,c,d
sim.setNeuronParameters(MEC_LII_Stellate, s_C, 0.0f, s_k, 0.0f, s_vr, 0.0f, s_vt, 
								0.0f, s_a, 0.0f, s_b, 0.0f, s_vpeak, 0.0f, s_c, 0.0f, 
								s_d, 0.0f, 1);
sim.setNeuronParameters(EC_LII_Axo_Axonic, 115.0f, 0.0f, 2.32f, 0.0f, -57.15f, 0.0f, 
								-50.75f, 0.0f, 0.003f, 0.0f, 12.27f, 0.0f, 2.43f, 0.0f, 
								-60.23f, 0.0f, -2.0f, 0.0f, 1); 
sim.setNeuronParameters(MEC_LII_Basket, 115.0f, 0.0f, 2.32f, 0.0f, -57.15f, 0.0f, 
								-50.75f, 0.0f, 0.003f, 0.0f, 12.27f, 0.0f, 2.43f, 0.0f, 
								-60.23f, 0.0f, -2.0f, 0.0f, 1); 
sim.setNeuronParameters(EC_LII_Basket_Multipolar, 115.0f, 0.0f, 2.32f, 0.0f, -57.15f, 0.0f, 
								-50.75f, 0.0f, 0.003f, 0.0f, 12.27f, 0.0f, 2.43f, 0.0f, 
								-60.23f, 0.0f, -2.0f, 0.0f, 1); 
sim.setNeuronParameters(CA1_Pyramidal, 334.0f, 0.0f, 1.56f, 0.0f, -69.36f, 0.0f, -53.22f, 
								0.0f, 0.0f, 0.0f, -17.25f, 0.0f, 25.46f, 0.0f, -60.22f, 
								0.0f, 16.0f, 0.0f, 1);

/* neuron connection parameters */
setInExcConns(&sim, &p);
MexHatConnection* MexHatConn = new MexHatConnection(&p);
SomeToSomeConnection* SomeToSomeConn = new SomeToSomeConnection(&p);	
static const float g_val = 4.92;
sim.connect(MEC_LII_Stellate_ExtDir, MEC_LII_Stellate, "one-to-one", p.dir_to_gc_wt, 1.0f, 
			RangeDelay(1), RadiusRF(-1), SYN_PLASTIC, g_val, 0.0f); // 0 DIR
p.conn_offset = 0;
//sim.connect(MEC_LII_Stellate, EC_LII_Axo_Axonic, "one-to-one", 2000.0f, 1.0f, 
//			RangeDelay(1), RadiusRF(-1), SYN_PLASTIC, g_val, 0.0f); // 1 GC->IN
sim.connect(MEC_LII_Stellate, EC_LII_Axo_Axonic, SomeToSomeConn, SYN_FIXED, g_val, 0.0f);
sim.connect(EC_LII_Axo_Axonic, MEC_LII_Stellate, MexHatConn, SYN_FIXED, g_val, 0.0f); // 2 IN->GC one-to-many
p.conn_offset = 1;
MexHatConn = new MexHatConnection(&p);
SomeToSomeConn = new SomeToSomeConnection(&p);
sim.connect(MEC_LII_Stellate, MEC_LII_Basket, SomeToSomeConn, SYN_FIXED, g_val, 0.0f);
sim.connect(MEC_LII_Basket, MEC_LII_Stellate, MexHatConn, SYN_FIXED, g_val, 0.0f); // 2 IN->GC one-to-many
p.conn_offset = 2;
MexHatConn = new MexHatConnection(&p);
SomeToSomeConn = new SomeToSomeConnection(&p);
sim.connect(MEC_LII_Stellate, EC_LII_Basket_Multipolar, SomeToSomeConn, SYN_FIXED, g_val, 0.0f);
sim.connect(EC_LII_Basket_Multipolar, MEC_LII_Stellate, MexHatConn, SYN_FIXED, g_val, 0.0f); // 2 IN->GC one-to-many
sim.connect(CA1_Pyramidal, MEC_LII_Stellate, "one-to-one", 1.0f, 1.0f, 
			RangeDelay(1), RadiusRF(-1), SYN_PLASTIC, g_val, 0.0f); // 3 PCs

/* STP parameters */
static const float m1 = 0.1231;//0.0001; // 0-1 range
static const float m2 = 49.71;//1000;
static const float m3 = 153.4;//1000;//0.0001;
static const float m4 = 6.674;//0.0001; 
static const float m5 = 150.0;//1000;
static const float m6 = 6.0;//1000;//0.0001;
static const float m7 = 150.0;//0.0001; 
sim.setSTP(MEC_LII_Stellate_ExtDir, MEC_LII_Stellate, true, STPu(m1, 0.0f),
                                     STPtauU(m2, 0.0f),
                                     STPtauX(m3, 0.0f),
                                     STPtdAMPA(m4, 0.0f),
                                     STPtdNMDA(m5, 0.0f),
                                     STPtdGABAa(m6, 0.0f),
                                     STPtdGABAb(m7, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate, EC_LII_Axo_Axonic, true, STPu(m1, 0.0f),
                                     STPtauU(m2, 0.0f),
                                     STPtauX(m3, 0.0f),
                                     STPtdAMPA(m4, 0.0f),
                                     STPtdNMDA(m5, 0.0f),
                                     STPtdGABAa(m6, 0.0f),
                                     STPtdGABAb(m7, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate, MEC_LII_Basket, true, STPu(m1, 0.0f),
                                     STPtauU(m2, 0.0f),
                                     STPtauX(m3, 0.0f),
                                     STPtdAMPA(m4, 0.0f),
                                     STPtdNMDA(m5, 0.0f),
                                     STPtdGABAa(m6, 0.0f),
                                     STPtdGABAb(m7, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate, EC_LII_Basket_Multipolar, true, STPu(m1, 0.0f),
                                     STPtauU(m2, 0.0f),
                                     STPtauX(m3, 0.0f),
                                     STPtdAMPA(m4, 0.0f),
                                     STPtdNMDA(m5, 0.0f),
                                     STPtdGABAa(m6, 0.0f),
                                     STPtdGABAb(m7, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(EC_LII_Axo_Axonic, MEC_LII_Stellate, true, STPu(0.1278, 0.0f),
                                     STPtauU(37.06, 0.0f),
                                     STPtauX(314.1, 0.0f),
                                     STPtdAMPA(5.0f, 0.0f),
                                     STPtdNMDA(150.0f, 0.0f),
                                     STPtdGABAa(9.17f, 0.0f),
                                     STPtdGABAb(150.0f, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Basket, MEC_LII_Stellate, true, STPu(0.1278, 0.0f),
                                     STPtauU(37.06, 0.0f),
                                     STPtauX(314.1, 0.0f),
                                     STPtdAMPA(5.0f, 0.0f),
                                     STPtdNMDA(150.0f, 0.0f),
                                     STPtdGABAa(9.17f, 0.0f),
                                     STPtdGABAb(150.0f, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(EC_LII_Basket_Multipolar, MEC_LII_Stellate, true, STPu(0.1278, 0.0f),
                                     STPtauU(37.06, 0.0f),
                                     STPtauX(314.1, 0.0f),
                                     STPtdAMPA(5.0f, 0.0f),
                                     STPtdNMDA(150.0f, 0.0f),
                                     STPtdGABAa(9.17f, 0.0f),
                                     STPtdGABAb(150.0f, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(CA1_Pyramidal, MEC_LII_Stellate, true, STPu(m1, 0.0f),
                                     STPtauU(m2, 0.0f),
                                     STPtauX(m3, 0.0f),
                                     STPtdAMPA(m4, 0.0f),
                                     STPtdNMDA(m5, 0.0f),
                                     STPtdGABAa(m6, 0.0f),
                                     STPtdGABAb(m7, 0.0f),
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