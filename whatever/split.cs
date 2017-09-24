using System;

class Split
{    
	void        splitServerString(string s)
	{
		if (s == NULL)
			return ;

		string[] args = s.Split(" ");

		switch (args[0])
		{
			case "msz":
				//msz(Convert.ToInt32(args[1]), Convert.ToInt32(args[2]));
				break;
			case "bct":
				//bct(Convert.ToInt32(args[1]), Convert.ToInt32(args[2]), 
					//Convert.ToInt32(args[3]),
					//Convert.ToInt32(args[4]), 
					//Convert.ToInt32(args[5]), 
					//Convert.ToInt32(args[6]),
					//Convert.ToInt32(args[7]),
					//Convert.ToInt32(args[8]),
					//Convert.ToInt32(args[9]));
				break;
			case "tna":
				//tna(args[1]);
				break;
			case "pnw":
				//pnw(Convert.ToInt32(args[1]),
					//Convert.ToInt32(args[2]),
					//Convert.ToInt32(args[3]), args[4],
					//Convert.ToInt32(args[5]), args[5]);
				break;
			case "ppo":
				//ppo(Convert.ToInt32(args[1]), Convert.ToInt32(args[2]), Convert.ToInt32(args[3]), args[4]);
				break;
			case "plv":
				//plv(Convert.ToInt32(args[1]), Convert.ToInt32(args[2]));
				break;
			case "pin":
				//pin(Convert.ToInt32(args[1]), Convert.ToInt32(args[2]), Convert.ToInt32(args[3]),
					//Convert.ToInt32(args[4]),
					//Convert.ToInt32(args[5]),
					//Convert.ToInt32(args[6]),
					//Convert.ToInt32(args[7]),
					//Convert.ToInt32(args[8]),
					//Convert.ToInt32(args[9]),
					//Convert.ToInt32(args[10]));
				break;
			case "pex":
				//pex(Convert.ToInt32(args[1]));
				break;
			case "pbc":
				//pbc(Convert.ToInt32(args[1]), args[2]);
				break;
			case "pic":
				int	[]	players = new int[args.Length - 4];
				for (int i = 0; i < (args.Length - 4); i++)
					players[i] = Convert.ToInt32(args[i + 4]);
				//pic(Convert.ToInt32(args[1]), Convert.ToInt32(args[2]), Convert.ToInt32(args[3]), players);
				break;
			case "pie":
				//pie(Convert.ToInt32(args[1]), Convert.ToInt32(args[2]), args[3]);
				break;
			case "pfk":
				//pfk(Convert.ToInt32(args[1]));
				break;
			case "pdr":
				//pfk(Convert.ToInt32(args[1]));
				break;
			case "pgt":
				//pfk(Convert.ToInt32(args[1]));
				break;
			case "pdi":
				//pfk(Convert.ToInt32(args[1]));
				break;
			case "enw":
				//enw(Convert.ToInt32(args[1]), Convert.ToInt32(args[2]), Convert.ToInt32(args[3]), Convert.ToInt32(args[4]));
				break;
			case "eht":
				//eht(Convert.ToInt32(args[1]));
				break;
			case "ebo":
				//ebo(Convert.ToInt32(args[1]));
				break;
			case "edi":
				//edi(Convert.ToInt32(args[1]));
				break;
			case "sgt":
				//sgt(Convert.ToInt32(args[1]));
				break;
			case "seg":
				//seg(args[1]);
				break;
			case "smg":
				//smg(args[1]);
				break;
			case "suc":
				//suc();
				break;
			case "sbp":
				//sbp();
				break;
			default:
				//Incorrect Commands...
				break;
		}
	}
}